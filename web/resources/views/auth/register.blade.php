@extends('layouts.layout')

@section('app', 'register')

@section('css')
	<link rel="stylesheet" type="text/css" href="{{ url('css/auth/register.css') }}" />
@endsection

@section('javascript')
	<script type="text/javascript" src="{{ url('js/auth/register.js') }}"></script>
@endsection

@section('content')
	<div class="container">
		<form name="form" class="form-horizontal" ng-control="RegisterController" novalidate>
            <div class="form-group">
                <label for="txtUserName" class="col-sm-4 control-label">User&nbsp;&nbsp;Name</label>
                <div class="col-sm-5">
                    <input type="text" id="txtUserName" name="userName" class="form-control" ng-model="user.userName" required/>
                    <p class="text-danger" ng-show="(form.$submitted || form.userName.$touched) && form.userName.$error.required">
                        Please&nbsp;Enter&nbsp;User&nbsp;Name
                    </p>
                </div>
            </div>
            <div class="form-group">
                <label for="txtEmail" class="col-sm-4 control-label">Email</label>
                <div class="col-sm-5">
                    <input type="email" id="txtEmail" name="email" class="form-control" ng-model="user.email" required/>
                    <p class="text-danger" ng-show="(form.$submitted || form.email.$touched) && form.email.$error.required">
                        Please&nbsp;Enter&nbsp;Email
                    </p>
                    <p class="text-danger" ng-show="(form.$submitted || form.email.$touched) && form.email.$error.email">
                        Please&nbsp;Enter&nbsp;Valid&nbsp;Email&nbsp;Address
                    </p>
                </div>
            </div>
            <div class="form-group">
                <label for="txtPassword" class="col-sm-4 control-label">Password</label>
                <div class="col-sm-5">
                    <input type="password" id="txtPassword" name="password" class="form-control" ng-model="user.password" required/>
                    <p class="text-danger" ng-show="(form.$submitted || form.password.$touched) && form.password.$error.required">
                        Please&nbsp;Enter&nbsp;Password
                    </p>
                </div>
            </div>
            <div class="form-group">
                <label for="txtConfirmPwd" class="col-sm-4 control-label">Conform&nbsp;&nbsp;Password</label>
                <div class="col-sm-5">
                    <input type="password" id="txtConfirmPwd" name="confirmPwd" class="form-control" ng-model="user.confirmPwd" ng-pattern="user.password" required/>
                    <p class="text-danger" ng-show="(form.$submitted || form.confirmPwd.$touched) && form.confirmPwd.$error.required">
                        Please&nbsp;Conform&nbsp;Your&nbsp;Password
                    </p>
                    <p class="text-danger" ng-show="(form.$submitted || form.confirmPwd.$touched) && form.confirmPwd.$error.pattern">
                        Not&nbsp;The&nbsp;Same&nbsp;Password
                    </p>
                </div>
            </div>
            <div class="form-group">
                <label class="col-sm-4 control-label">Do&nbsp;You&nbsp;Know&nbsp;Phospher?</label>
                <div class="col-sm-5">
                    <label class="radio-inline">
                        <input type="radio" name="known" value="yes" ng-model="user.known" required> Yes
                    </label>
                    <label class="radio-inline">
                        <input type="radio" name="known" value="no" ng-model="user.known" required> No
                    </label>
                    <p class="text-danger" ng-show="(form.$submitted || form.known.$touched) && form.known.$error.required">
                        Do&nbsp;You&nbsp;Know&nbsp;Phospher?
                    </p>
                </div>
            </div>
            <div class="form-group" ng-show="user.known == 'yes'">
                <label class="col-sm-4 control-label">Is&nbsp;He&nbsp;Handsome?</label>
                <div class="col-sm-5">
                    <label class="radio-inline">
                        <input type="radio" name="handsome" value="yes" ng-model="user.handsome" required> Yes
                    </label>
                    <label class="radio-inline">
                        <input type="radio" name="handsome" value="no" ng-model="user.handsome" required> No
                    </label>
                    <p class="text-danger" ng-show="(form.$submitted || form.handsome.$touched) && user.known == 'yes' && form.handsome.$error.required">
                        Is&nbsp;He&nbsp;Handsome?
                    </p>
                </div>
            </div>
            <div class="form-group">
                <div class="col-sm-4"></div>
                <div class="col-sm-5">
                    <input type="submit" class="btn" value="Submit" ng-click="register(user)" />
                </div>
            </div>
        </form>
	</div>
@endsection