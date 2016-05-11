@extends('layouts.layout')

@section('app', 'login')

@section('css')
    <link rel="stylesheet" type="text/css" href="{{ url('css/auth/login.css') }}" />
@endsection

@section('javascript')
    <script type="text/javascript" src="{{ url('js/auth/login.js') }}"></script>
@endsection

@section('content')
    <div class="container" ng-controller="LoginController">
        <div class="page-header">
            <h3>Login</h3>
        </div>
        @if (count($errors) > 0)
            <div class="text-danger error-message">
                @foreach ($errors->all() as $error)
                    <p>{{ $error }}</p>
                @endforeach
            </div>
        @endif
        <form id="loginForm" name="form" class="form-horizontal" method="post" ng-submit="form.$valid && submit()" novalidate>
            {{ csrf_field() }}
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
                <div class="col-sm-4"></div>
                <div class="col-sm-5">
                    <input type="submit" class="btn" value="Login" />
                    <a href="{{ action('Auth\AuthController@showRegistrationForm') }}" class="register-link">Register</a>
                </div>
            </div>
        </form>
    </div>
@endsection