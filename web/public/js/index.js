var app = angular.module('index', ['ngTouch', 'ui.grid']);

app.controller('LatestController', ['$scope', '$http', '$interval', '$window', function ($scope, $http, $interval, $window) {

	getSystemInfo = function (callback) {
		$http.get('/SystemInfo/Last5Min').then(function (response) {

			var data = [];

			for (var i = 0; i < response.data.length; i++) {
				data[i] = {
					ip: response.data[i].IPAddress,
					cpu: (response.data[i].CPUUsage * 100).toFixed(2),
					mem: (response.data[i].MemoryUsage * 100).toFixed(2)
				};
			}

			$scope.gridOption.data = data;
			if (callback) {
				callback();
			}
		});
	}

	getSystemInfo(function () {
		$interval(function () {
			getSystemInfo();
		}, 5000);
	});
	
	$scope.toMachineDetailPage = function (ip) {
		$window.location.href = '/machinedetail/' + decodeURIComponent(ip);
	};

	$scope.gridOption = {
		columnDefs: [
			{ name: 'IP Address', field: 'ip' },
			{ name: 'CPU Usage Avg(%)', field: 'cpu', cellClass: 'percent-cell' },
			{ name: 'Mem Usage Avg(%)', field: 'mem', cellClass: 'percent-cell' },
			{ name: '', field: 'ip', cellTemplate: '<div class="ui-grid-cell-contents ng-binding"><a href="javascript:void(0);" ng-click="grid.appScope.toMachineDetailPage(COL_FIELD)">Detail</a></div>' }
		],
		data: []
	};
}]);