var app = angular.module('detail', ['ngTouch', 'highcharts-ng']);

app.controller('ProcessStatesController', ['$scope', '$interval', '$http', function ($scope, $interval, $http) {
    Highcharts.setOptions({
        global: {
            useUTC: false
        }
    });

    $scope.ip = '';
    $scope.cpuChartConfig = {
        options: {
            chart: {
                type: 'spline'
            }
        },
        title: {
            text: 'Process CPU Usage'
        },
        subtitle: {
            text: 'refresh every 10 sec.'
        },
        xAxis: {
            type: 'datetime',
            tickPixelInterval: 150
        },
        yAxis: {
            title: {
                text: 'CPU Usage(%)'
            },
            max: 100,
            min: 0
        }
    };
    
    $scope.memoryChartConfig = {
        options: {
            chart: {
                type: 'spline'
            }
        },
        title: {
            text: 'Process Memory Usage'
        },
        subtitle: {
            text: 'refresh every 10 sec.'
        },
        xAxis: {
            type: 'datetime',
            tickPixelInterval: 150
        },
        yAxis: {
            title: {
                text: 'Memory Usage(%)'
            },
            max: 100,
            min: 0
        }
    }

    var findSerie = function (seriesName, series) {
        for (var i = 0; i < series.length; i++) {
            if (seriesName = series[i].name) {
                return series[i];
            }
        }

        return null;
    }

    var addSeriesToChart = function (seriesName, chartObj) {
        chartObj.addSeries({
            name: seriesName,
            data: (function () {
                var data = [];
                var time = [];
                if (chartObj.series.length > 0) {
                    for (var i = 0; i < chartObj.series[0].data.length; i++) {
                        time.push(series[0].data[i].x);
                    }
                } else {
                    var endTime = (new Date()).getTime();
                    for (var i = -19; i <= 0; i++) {
                        time.push(endTime + i * 10000);
                    }
                }
                for (var i = 0; i < time.length - 1; i++) {
                    data.push({
                        x: time[i],
                        y: 0
                    });
                }

                return data;
            } ())
        });

        return chartObj.series[chartObj.series.length - 1];
    }

    var displayLineChart = function (chartObj, data, displayField) {
        for (var i = 0; i < data.length; i++) {
                var serie = findSerie(data[i]['_id'], chartObj.series);
                if (serie == null) {
                    serie = addSeriesToChart(data[i]['_id'], chartObj);
                }
                var x = (new Date()).getTime();
                var y = data[i][displayField];
                serie.addPoint([x, y], true, true)
            }
    };

    var getProcessStatus = function () {
        $http.get('/SystemInfo/Detail/' + $scope.ip + '/ProcessStates').then(function (response) {
            var data = response.data;
            displayLineChart($scope.cpuChartConfig.getHighcharts(), data, 'CPUUsage');
            displayLineChart($scope.memoryChartConfig.getHighcharts(), data, 'MemoryUsage');
        });
    };

    $scope.cpuChartConfig.options.chart.events = {
        load: function () {
            getProcessStatus();
            $interval(function () {
                getProcessStatus();
            }.bind(this), 10000);
        }
    }
}]);