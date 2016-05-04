var app = angular.module('index', ['ngTouch', 'ui.grid']);

app.controller('LatestController', ['$scope', '$http', '$interval', function ($scope, $http, $interval) {

	getSystemInfo = function (callback) {
		$http.get('/GetSystemInfo').then(function (response) {

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

	$scope.gridOption = {
		columnDefs: [
			{ name: 'IP Address', field: 'ip' },
			{ name: 'CPU Usage Avg(%)', field: 'cpu', cellClass: 'percent-cell' },
			{ name: 'Mem Usage Avg(%)', field: 'mem', cellClass: 'percent-cell' }
		],
		data: []
	};
}]);