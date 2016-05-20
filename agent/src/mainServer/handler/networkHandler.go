package handler

import (
	"encoding/json"
	"io/ioutil"
	"log"
	"mainServer/config"
	"mainServer/persist"
	"net"
	"utils"
)

type NetworkHandler struct {
	machineRecordRepository *persist.MachineRecordRepository
	systemInfoRepository    *persist.SystemInfoRepository
	systemInfoChan          chan *utils.SystemInfo
}

func (handler *NetworkHandler) StartPersitMessage() {
	go func() {
		for {
			systemInfo := <-handler.systemInfoChan
			perr := (*handler.machineRecordRepository).AddMachineRecord(persist.MachineRecord{IpAddress: systemInfo.IPAddress, MacAddress: systemInfo.MacAddress})
			if perr != nil {
				log.Fatalln(perr.Error())
			}

			perr = (*handler.systemInfoRepository).PersistSystemInfo(systemInfo)
			if perr != nil {
				log.Fatalln(perr.Error())
			}
		}
	}()
}

func (handler *NetworkHandler) StartNetwork() error {
	if port, err := config.GetListeningPort(); err == nil {
		l, err := net.Listen("tcp", ":"+port)
		if err != nil {
			return err
		}
		defer l.Close()

		for {
			conn, err := l.Accept()
			if err != nil {
				log.Println(err)
				continue
			}

			go handler.handleConnection(conn)
		}
	} else {
		return err
	}
}

func (handler *NetworkHandler) handleConnection(conn net.Conn) {
	defer conn.Close()

	data, err := ioutil.ReadAll(conn)
	if err != nil {
		log.Println(err)
		return
	}

	var message utils.Message
	err = json.Unmarshal(data, &message)
	if err != nil {
		log.Println(err)
		return
	}

	if message.Type == "INFO" {
		err = handler.prepareSaveSystemInfo(message.Content)
		if err != nil {
			log.Fatalln(err)
		}
	}
}

func (handler *NetworkHandler) prepareSaveSystemInfo(systemInfoJson string) error {
	var systemInfo utils.SystemInfo
	err := json.Unmarshal([]byte(systemInfoJson), &systemInfo)
	if err != nil {
		return err
	}

	handler.systemInfoChan <- &systemInfo
	return nil
}

func NewNetworkHandler(machineRecordRepository *persist.MachineRecordRepository, systemInfoRepository *persist.SystemInfoRepository) *NetworkHandler {
	return &NetworkHandler{machineRecordRepository: machineRecordRepository, systemInfoRepository: systemInfoRepository, systemInfoChan: make(chan *utils.SystemInfo, 1000)}
}
