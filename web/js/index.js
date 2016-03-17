var app = angular.module('index', ['ngTouch', 'ui.grid']);

app.controller('LatestController', ['$scope', function ($scope) {
	$scope.gridOption = {
		columnDefs: [
			{ name: 'IP Address', field: 'ip' },
			{ name: 'CPU Usage Avg(%)', field: 'cpu' },
			{ name: 'Mem Usage Avg(%)', field: 'mem' }
		],
		data: [
			{
				'ip': '10.10.10.10',
				'cpu': 30,
				'mem': 10
			},
			{
				'ip': '10.10.10.10',
				'cpu': 30,
				'mem': 10
			},
			{
				'ip': '10.10.10.10',
				'cpu': 30,
				'mem': 10
			}
		]
	};
}]);