package main

import (
	"encoding/json"
	"gopkg.in/mgo.v2"
	"io/ioutil"
	"log"
	"mainServer/config"
	"net"
	"utils"
)

var systemInfoChan chan *utils.SystemInfo

func init() {
	systemInfoChan = make(chan *utils.SystemInfo, 1000)
}

func main() {
	go func() {
		for {
			persistSystemInfo(<-systemInfoChan)
		}
	}()

	err := startNetwork()
	if err != nil {
		log.Fatalln(err.Error())
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
		log.Println(err.Error())
		return
	}

	var message utils.Message
	err = json.Unmarshal(data, &message)
	if err != nil {
		log.Println(err.Error())
		return
	}

	if message.Type == "INFO" {
		prepareSaveSystemInfo(message.Content)
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
