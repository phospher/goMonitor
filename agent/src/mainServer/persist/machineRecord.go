package persist

import (
	"reflect"
	"utils"
)

var machineRecordRepositoryType reflect.Type

type MachineRecord struct {
	Id            int64
	IpAddress     string
	MacAddress    string
	CreatedAt     int64 `xorm:"created"`
	LastUpdatedAt int64 `xorm:"updated"`
}

type MachineRecordRepository interface {
	AddMachineRecord(machineRecord MachineRecord) error
}

func RegisterMachineRecordRepository(repository interface{}) {
	utils.RegisterIocImplement("MachineRecordRepository", repository)
}

func NewMachineRepository() (*MachineRecordRepository, error) {
	result, err := utils.NewImplement("MachineRecordRepository")
	if err == nil {
		resultRepository := result.(MachineRecordRepository)
		return &resultRepository, nil
	} else {
		return nil, err
	}
}
