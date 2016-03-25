@extends('layouts.layout')

@section('css')
	<link rel="stylesheet" type="text/css" href="{{ url('lib/ui-grid/ui-grid.min.css') }}" />
	<style type="text/css">
		.ui-grid { color: #242729; }

		.ui-grid-header, .ui-grid-column-menu { color: #fff; }
	</style>
@endsection

@section('javascript')
	<script type="text/javascript" src="{{ url('lib/ui-grid/ui-grid.min.js') }}"></script>
	<script type="text/javascript" src="{{ url('js/index.js') }}"></script>
@endsection

@section('content')
	<div class="container">
		<div class="page-header" style="margin-top: 0px;">
			<h4>Last&nbsp;5&nbsp;minutes&nbsp;system&nbsp;state</h4>
		</div>
		<div ng-controller="LatestController">
			<div id="latestGrid" ui-grid="gridOption" class="grid"></div>
		</div>
	</div>
@endsection