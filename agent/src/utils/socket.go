package utils

import (
	"encoding/json"
	"net"
)

type Message struct {
	Type    string
	Content string
}

func SendMessage(address string, message *Message) error {
	conn, err := net.Dial("tcp", address)
	if err != nil {
		return err
	}
	defer conn.Close()

	content, err := json.Marshal(message)
	if err != nil {
		return err
	}

	_, err = conn.Write(content)
	return err
}
