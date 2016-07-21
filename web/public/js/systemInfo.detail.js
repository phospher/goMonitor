var app = angular.module('detail', ['ngTouch', 'highcharts-ng']);

app.controller('ProcessStatesController', ['$scope', '$interval', function ($scope, $interval) {
    $scope.ip = '';
    $scope.chartConfig = {
        title: {
            text: 'Process States'
        },
        subtitle: {
            text: 'refresh every 10 sec.'
        },
        xAxis: {
            categories: ['5s']
        },
        yAxis: {
            title: {
                text: 'CPU Usage(%)'
            }
        },
        series: [
            {
                name: 'chrome',
                data: [Math.random()]
            }
        ]
    };

    var second = 5;

    $interval(function () {
        second += 5;
        if ($scope.chartConfig.series[0].data.length >= 5) {
            $scope.chartConfig.series[0].data.splice(0, 1);
        }
        $scope.chartConfig.xAxis.categories.push(second + 's');
        $scope.chartConfig.series[0].data[$scope.chartConfig.series[0].data.length] = Math.random();
    }, 5000);
}]);