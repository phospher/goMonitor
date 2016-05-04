package main

import (
	"encoding/json"
	"io/ioutil"
	"log"
	"mainServer/config"
	"net"
	"utils"

	"gopkg.in/mgo.v2"
)

var systemInfoChan chan *utils.SystemInfo

func init() {
	systemInfoChan = make(chan *utils.SystemInfo, 1000)
}

func main() {
	go func() {
		for {
			perr := persistSystemInfo(<-systemInfoChan)
			if perr != nil {
				log.Fatalln(perr)
			}
		}
	}()

	err := startNetwork()
	if err != nil {
		log.Fatalln(err)
	}
}

func persistSystemInfo(systemInfo *utils.SystemInfo) error {
	connStr, err := config.GetDBConnectionString()
	if err != nil {
		return err
	}

	session, err := mgo.Dial(connStr)
	if err != nil {
		return err
	}

	collection := session.DB("Monitor").C("SystemInfo")
	return collection.Insert(systemInfo)
}

func startNetwork() error {
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

			go handleConnection(conn)
		}
	} else {
		return err
	}
}

func handleConnection(conn net.Conn) {
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
		err = prepareSaveSystemInfo(message.Content)
		if err != nil {
			log.Fatalln(err)
		}
	}
}

func prepareSaveSystemInfo(systemInfoJson string) error {
	var systemInfo utils.SystemInfo
	err := json.Unmarshal([]byte(systemInfoJson), &systemInfo)
	if err != nil {
		return err
	}

	systemInfoChan <- &systemInfo
	return nil
}
