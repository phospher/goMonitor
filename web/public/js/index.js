var app = angular.module('index', ['ngTouch', 'ui.grid']);

app.controller('LatestController', ['$scope', '$http', function ($scope, $http) {

	$http.get('/GetSystemInfo').then(function (response) {

		var data = [];

		for (var i = 0; i < response.data.length; i++) {
			data[i] = {
				ip: response.data[i].IPAddress,
				cpu: response.data[i].CPUUsage,
				mem: response.data[i].MemoryUsage
			};
		}

		$scope.gridOption.data = data;
	});

	$scope.gridOption = {
		columnDefs: [
			{ name: 'IP Address', field: 'ip' },
			{ name: 'CPU Usage Avg(%)', field: 'cpu' },
			{ name: 'Mem Usage Avg(%)', field: 'mem' }
		],
		data: []
	};
}]);