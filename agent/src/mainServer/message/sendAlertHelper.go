package message

type AlertMessage struct {
	To      string
	Subject string
	Content string
}

type SendAlertHelper interface {
	Send(message *AlertMessage) error
}

var sendAlertHelper *SendAlertHelper

func InitSendAlertHelper(sendAlertHelper SendAlertHelper) error {
	//value := reflect.ValueOf(sendAlertHelper)
	return nil
}
