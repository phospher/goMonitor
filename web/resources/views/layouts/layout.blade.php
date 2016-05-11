<!DOCTYPE html>
<html ng-app="@yield('app')">
<head>
	<meta charset="utf-8" />
	<meta http-equiv="X-UA-Compatible" content="IE=10;" />
	<link rel="stylesheet" type="text/css" href="{{ url('lib/bootstrap/css/bootstrap.min.css') }}" />
	<title>Dash Borad</title>
	@yield('css')
</head>
<body>
	<div class="navbar navbar-default">
		<div class="container">
			<div class="navbar-header">
				<a href="#" class="navbar-brand">
					Dash&nbsp;Borad
				</a>
			</div>
			@if(Auth::check())
				<ul class="nav navbar-nav navbar-right">
					<li><a href="{{ action('Auth\AuthController@logout') }}">Logout</a></li>
				</ul>
			@endif
		</div>
	</div>
	@yield('content')
	<script type="text/javascript" src="{{ url('lib/angularjs/angular.min.js') }}"></script>
	<script type="text/javascript" src="{{ url('lib/angularjs/angular-animate.min.js') }}"></script>
	<script type="text/javascript" src="{{ url('lib/angularjs/angular-touch.min.js') }}"></script>
	@yield('javascript')
</body>
</html>