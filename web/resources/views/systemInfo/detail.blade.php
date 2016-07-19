@extends('layouts.layout')

@section('app', 'detail')

@section('css')
    <link rel="stylesheet" type="text/css" href="{{ url('css/systemInfo.detail.css') }}" />
@endsection

@section('javascript')
    <script type="text/javascript" src="{{ url('js/systemInfo.detail.js') }}"></script>
@endsection

@section('content')
    <div class="container">
        <div class="page-header" style="margin-top: 0px;">
			<h4>IP Address: {{ $ip }}</h4>
		</div>
        <div ng-controller="ProcessStatesController">
            <input type="hidden" name="ip" ng-model="ip" ng-init="ip='{{ $ip }}'" />
            @{{ip}}
        </div>
    </div>
@endsection