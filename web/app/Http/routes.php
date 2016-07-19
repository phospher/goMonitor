<?php

/*
-----------------------------------------------------------------
| Application Routes
|--------------------------------------------------------------------------
|
| Here is where you can register all of the routes for an application.
| It's a breeze. Simply tell Laravel the URIs it should respond to
| and give it the controller to call when that URI is requested.
|
*/
Route::group(['middleware'=>'auth'], function() 
{
    
    Route::get('/', function() {
        return view('index');
    });
    
    Route::get('/SystemInfo/Last5Min', 'SystemInfoController@GetLast5MinutesSystemInfo');
    
    Route::get('/SystemInfo/Detail/{ip}', 'SystemInfoController@GetMachineDetail');
});

Route::auth();
