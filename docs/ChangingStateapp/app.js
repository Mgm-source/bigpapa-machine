angular.module('routingApp',['ui.router'])
.controller("routingAppController",function($state,$location){
    // needed otherwise js doesnt know where to look
    var self = this;
// html go button; reference basically 
    self.go = function(page){
        //$go Transition to a different state
        $state.go(page);
        console.log($state.go(page));
       /* Code below not needed, '$state' does the url change*/
                    // $location.path(page);

    };

})
 // Basically a constructor just choose the same name as the services, just not to get confused 
.config(['$stateProvider','$urlServiceProvider',function($stateProvider,$urlServiceProvider){

    $stateProvider
    // different states 
    .state('Index', {
        url:'/Index',
        templateUrl:"views/index.html",
        
    })
    // different states 
    .state('Name', {
        url:'/Name',
        templateUrl:"views/Entername.html",
 
    })
    // this has the otherwise stuff
    $urlServiceProvider.rules
    .otherwise('/index');
    
}]);
