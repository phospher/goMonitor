package utils

import (
	"fmt"
	"reflect"
)

var typeMap map[string]reflect.Type

func init() {
	typeMap = make(map[string]reflect.Type)
}

func RegisterIocImplement(interfaceName string, implement interface{}) {
	repositoryValue := reflect.ValueOf(implement)
	if repositoryValue.Kind() == reflect.Ptr {
		repositoryValue = repositoryValue.Elem()
	}
	typeMap[interfaceName] = repositoryValue.Type()
}

func NewImplement(interfaceName string) (interface{}, error) {
	implement, ok := typeMap[interfaceName]
	if !ok {
		return nil, fmt.Errorf("Can not found implement of %s", interfaceName)
	}
	return reflect.New(implement).Interface(), nil
}
