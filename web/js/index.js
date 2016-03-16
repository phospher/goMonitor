var app = angular.module('app', ['ngTouch', 'ui.grid']);

app.controller('LatestController', ['$scope', function ($scope) {
	$scope.data = [
		{
			'column1': 1,
			'column2': 'test'
		},
		{
			'column1': 2,
			'column2': 'test'
		},
		{
			'column1': 3,
			'column2': 'test'
		}
	];
}]);