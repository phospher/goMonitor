package persist

import "utils"

type SystemInfoRepository interface {
	PersistSystemInfo(systemInfo *utils.SystemInfo) error
}

func RegisterSystemInfoRepository(repository interface{}) {
	utils.RegisterIocImplement("SystemInfoRepository", repository)
}

func NewSystemInfoRepository() (*SystemInfoRepository, error) {
	result, err := utils.NewImplement("SystemInfoRepository")
	if err == nil {
		resultRepository := result.(SystemInfoRepository)
		return &resultRepository, nil
	} else {
		return nil, err
	}
}
