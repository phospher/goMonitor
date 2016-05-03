<?php 

namespace App\Services;

use App\Contracts\SystemInfoRepository;
use App\SystemInfo;

class MongoSystemInfoRepository implements SystemInfoRepository {
    
    public function GetLast5MinuteSystemInfo()
    {
        return SystemInfo::all();
    }
    
}