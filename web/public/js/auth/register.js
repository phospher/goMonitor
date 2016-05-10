var app = angular.module('register', []);

app.directive('compareTo', function () {
     return {
         require: '?ngModel',
         link: function(scope, elm, attrs, ctrl) {
             ctrl.$validators.compareTo = function(modelValue, viewValue) {
                 if (ctrl.$isEmpty(modelValue)) {
                     return true;
                 }
                 return modelValue == attrs.compareTo;
             }
         }
     }
});

app.controller('RegisterController', ['$scope', function($scope, $http) {

}]);