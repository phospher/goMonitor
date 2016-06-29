package handler

import (
	"errors"
	"mainServer/filter"
	"reflect"
)

var systemInfoFilters []reflect.Type

func AddSystemInfoFilter(systeInfoFilter filter.SystemInfoFilter) error {
	if systeInfoFilter == nil {
		return errors.New("Object can not be null")
	}
	valueType := reflect.TypeOf(systeInfoFilter)
	systemInfoFilters = append(systemInfoFilters, valueType)

	return nil
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
