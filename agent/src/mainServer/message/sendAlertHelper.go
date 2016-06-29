package message

type AlertMessage struct {
	To      string
	Subject string
	Content string
}

type SendAlertHelper interface {
	Send(message *AlertMessage) error
}

var sendAlertHelper SendAlertHelper

func InitSendAlertHelper(sendAlertHelperImpl SendAlertHelper) {
	sendAlertHelper = sendAlertHelperImpl
}

func SendAlert(message *AlertMessage) error {
	return sendAlertHelper.Send(message)
}
