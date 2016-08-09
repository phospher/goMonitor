<?php 

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Symfony\Component\HttpFoundation\StreamedResponse;

use App\Http\Requests;
use App\Contracts\SystemInfoRepository;

use Log;

class SystemInfoController extends Controller {

    private $systemInfoRepository;

    public function __construct(SystemInfoRepository $systemInfoRepository) {
        $this->systemInfoRepository = $systemInfoRepository;
    }

    public function GetLast5MinutesSystemInfo(Request $request) {
        if ($request->header('Accept') == 'text/event-stream') {
            return new StreamedResponse(function () {
                while (true) {
                    $result = $this->systemInfoRepository->GetLast5MinuteSystemInfo();
                    if(count($result) != 0){
                        echo 'data:' . json_encode($result) . PHP_EOL . PHP_EOL;
                        ob_flush();
                        flush();
                    }
                    
                    sleep(5);
                }
            }, 200, ['Content-Type' => 'text/event-stream']);
        } else {
            return response()->json($this->systemInfoRepository->GetLast5MinuteSystemInfo());
        }
    }
    
    public function GetProcessStatesByMachine(Request $request, $ip) {
        if($request->header('Accept') == 'text/event-stream') {
            return new StreamedResponse(function () use ($ip) {
                while (true) {
                    $result = $this->systemInfoRepository->GetProcessStatesByMachine($ip);
                    if(count($result) != 0) {
                        echo 'data:' . json_encode($result) . PHP_EOL. PHP_EOL;
                        ob_flush();
                        flush();
                    }
                    
                    sleep(10);
                }
            }, 200, ['Content-Type' => 'text/event-stream']);
        } else {
            return response()->json($this->systemInfoRepository->GetProcessStatesByMachine($ip));
        }
    }
    
    public function GetSystemInfoDetail($ip){
        return view("systemInfo/detail", ['ip' => $ip]);
    }
}