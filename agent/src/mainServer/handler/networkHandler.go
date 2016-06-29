package handler

import (
	"encoding/json"
	"io/ioutil"
	"log"
	"mainServer/config"
	"net"
	"utils"
)

type NetworkHandler struct {
	systemInfoChan chan *utils.SystemInfo
}

func (handler *NetworkHandler) StartPersitMessage() {
	go func() {
		for {
			systemInfo := <-handler.systemInfoChan
			systemInfoFilters := SystemInfoFiltersIter{}
			data := *systemInfo
			var err error
			for item := systemInfoFilters.Next(); item != nil; item = systemInfoFilters.Next() {
				data, err = (*item).Process(data)
				if err != nil {
					log.Fatalln(err.Error())
				}
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

func NewNetworkHandler() *NetworkHandler {
	return &NetworkHandler{systemInfoChan: make(chan *utils.SystemInfo, 1000)}
}
