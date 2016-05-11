var app = angular.module('login', []);

app.controller('LoginController', ['$scope', function($scope) {
    $scope.submit = function() {
        document.getElementById('loginForm').submit();
    };
}]);