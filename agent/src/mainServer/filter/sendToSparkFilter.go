package filter

import (
	"encoding/json"
	"log"
	"mainServer/config"
	"net"
	"time"
	"utils"
)

var listener net.Listener
var systemInfoChan chan *utils.SystemInfo

func init() {
	systemInfoChan = make(chan *utils.SystemInfo)

	sparkAddress, err := config.GetSparkStreamAddress()
	if err != nil {
		log.Println(err.Error())
		return
	}

	listener, err = net.Listen("tcp", sparkAddress)
	if err != nil {
		log.Println(err.Error())
	} else {
		log.Println("success listen")
	}

	go startSendSystemInfo()
}

func startSendSystemInfo() {
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Println(err.Error())
			return
		}
		go func(connection net.Conn) {
			log.Println("new connection")
			for {
				systemInfo := <-systemInfoChan
				jsonConetnt, err := json.Marshal(*systemInfo)
				if err != nil {
					log.Println(err.Error())
				} else {
					jsonText := string(jsonConetnt) + "\n"
					_, err = conn.Write([]byte(jsonText))
					if err != nil {
						log.Println(err.Error())
						connection.Close()
						if err != nil {
							log.Println(err.Error())
						}
						return
					} else {
						log.Print("sended: " + jsonText)
					}
				}
			}
		}(conn)
	}
}

type SendToSparkFilter struct {
}

func (this SendToSparkFilter) Process(systemInfo utils.SystemInfo) (utils.SystemInfo, error) {
	select {
	case systemInfoChan <- &systemInfo:
	case <-time.After(time.Second):
	}

	return systemInfo, nil
}
