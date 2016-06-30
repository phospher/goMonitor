package message

import (
	"log"
)

type LogSendAlertHelper struct {
}

func (this *LogSendAlertHelper) Send(message *AlertMessage) error {
	if message != nil {
		log.Println(message.Content)
	}
	return nil
}
