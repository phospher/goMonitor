var app = angular.module('register', []);

app.directive('radioRequired', function () {
     return {
         require: '?ngModel',
         scope: {
            modelField: '='  
         },
         link: function(scope, elm, attrs, ctrl) {
             ctrl.$validators.radioRequried = function(modelValue) {
                 alert(!ctrl.$isEmpty(modelValue))
                 return !ctrl.$isEmpty(modelValue);
             }
         }
     }
});

app.controller('RegisterController', ['$scope', function($scope) {
    $scope.register = function(user) {
          
    };
}]);