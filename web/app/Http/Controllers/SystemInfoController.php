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
    
    public function GetMachineDetail($ip) {
        return response()->json($this->systemInfoRepository->GetMachineDetail($ip));
    }
}