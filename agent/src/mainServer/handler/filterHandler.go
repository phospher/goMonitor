package handler

import (
	"errors"
	"mainServer/filter"
	"reflect"
)

var systemInfoFilters []reflect.Type

func AddSystemInfoFilter(systeInfoFilter interface{}) error {
	value := reflect.ValueOf(systeInfoFilter)
	if value.Kind() == reflect.Ptr {
		value = value.Elem()
	}

	filterInterfaceType := reflect.TypeOf((*filter.SystemInfoFilter)(nil)).Elem()
	valueType := value.Type()
	if valueType.Implements(filterInterfaceType) {
		systemInfoFilters = append(systemInfoFilters, valueType)
		return nil
	} else {
		return errors.New("Object must implement SystemInfoFilter")
	}
}

type SystemInfoFiltersIter struct {
	currentIndex int
}

func (this *SystemInfoFiltersIter) Next() *filter.SystemInfoFilter {

	if this.HasNext() {
		result := reflect.New(systemInfoFilters[this.currentIndex]).Interface().(filter.SystemInfoFilter)
		this.currentIndex++
		return &result
	} else {
		return nil
	}
}

func (this *SystemInfoFiltersIter) HasNext() bool {
	return this.currentIndex < len(systemInfoFilters)
}
