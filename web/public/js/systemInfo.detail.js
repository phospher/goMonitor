var app = angular.module('detail', ['ngTouch', 'highcharts-ng']);

app.controller('ProcessStatesController', ['$scope', '$interval', function ($scope, $interval) {
    Highcharts.setOptions({
        global: {
            useUTC: false
        }
    });

    $scope.ip = '';
    $scope.chartConfig = {
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
            }
        },
        series: [
            {
                name: 'chrome',
                data: (function () {
                    var data = [];
                    var time = (new Date()).getTime();
                    for (var i = -19; i <= 0; i++) {
                        data.push({
                            x: time + i * 5000,
                            y: 0
                        });
                    }

                    return data;
                } ())
            }
        ]
    };

    $scope.chartConfig.options.chart.events = {
        load: function () {
            var t = 0;
            $interval(function () {
                var series = this.series;
                var time = (new Date()).getTime();
                for (var i = 0; i < series.length; i++) {
                    var x = time;
                    var y = Math.random();
                    series[i].addPoint([x, y], true, true);
                }
                if (t == 6) {
                    this.addSeries({
                        name: 'safari',
                        data: (function () {
                            var data = [];
                            var time = (new Date()).getTime();
                            for (var i = -19; i <= 0; i++) {
                                data.push({
                                    x: time + i * 5000,
                                    y: 0
                                });
                            }

                            return data;
                        } ())
                    })
                }
                t++;
            }.bind(this), 5000);
        }
    }
}]);