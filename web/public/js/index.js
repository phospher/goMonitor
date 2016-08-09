var app = angular.module('index', ['ngTouch', 'ui.grid']);

app.controller('LatestController', ['$scope', '$http', '$interval', '$window', function ($scope, $http, $interval, $window) {
	$scope.result = '';
	
	setGridData = function (responseData) {
		var data = [];

		for (var i = 0; i < responseData.length; i++) {
			data[i] = {
				ip: responseData[i].IPAddress,
				cpu: (responseData[i].CPUUsage * 100).toFixed(2),
				mem: (responseData[i].MemoryUsage * 100).toFixed(2)
			};
		}
		$scope.gridOption.data = data;
	}

	if (EventSource != undefined) {
		var es = new EventSource('/SystemInfo/Last5Min');
		es.onmessage = function (event) {
			setGridData(JSON.parse(event.data));
			$scope.$apply();
		}
		$window.onbeforeunload = function() {
			es.close();	
		};
	} else {
		getSystemInfo = function (callback) {
			$http.get('/SystemInfo/Last5Min').then(function (response) {

				setGridData(response.data);

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
	}

	$scope.toMachineDetailPage = function (ip) {
		$window.location.href = '/SystemInfo/Detail/' + decodeURIComponent(ip);
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