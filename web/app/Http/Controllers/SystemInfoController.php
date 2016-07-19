<?php 

namespace App\Http\Controllers;

use Illuminate\Http\Request;

use App\Http\Requests;
use App\Contracts\SystemInfoRepository;

class SystemInfoController extends Controller {

    private $systemInfoRepository;

    public function __construct(SystemInfoRepository $systemInfoRepository) {
        $this->systemInfoRepository = $systemInfoRepository;
    }

    public function GetLast5MinutesSystemInfo() {
        return response()->json($this->systemInfoRepository->GetLast5MinuteSystemInfo());
    }
    
    public function GetProcessStatesByMachine($ip) {
        return response()->json($this->systemInfoRepository->GetProcessStatesByMachine($ip));
    }
    
    public function GetSystemInfoDetail($ip){
        return view("systemInfo/detail", ['ip' => $ip]);
    }
}