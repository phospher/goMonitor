var app = angular.module('detail', ['ngTouch', 'highcharts-ng']);

app.controller('ProcessStatesController', ['$scope', function ($scope) {
    $scope.ip = '';
    $scope.chartConfig = {
        title: {
            text: 'Process States'   
        },
        subtitle: {
            text: 'refresh every 10 sec.'
        }  
    };
}]);