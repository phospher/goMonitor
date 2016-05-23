package filter

import (
	"utils"
)

type SystemInfoFilter interface {
	Process(systemInfo utils.SystemInfo) (utils.SystemInfo, error)
}
