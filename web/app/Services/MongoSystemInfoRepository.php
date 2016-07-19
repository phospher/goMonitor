<?php 

namespace App\Services;

use App\Contracts\SystemInfoRepository;
use App\SystemInfo;
use Log;

class MongoSystemInfoRepository implements SystemInfoRepository {

    public function GetLast5MinuteSystemInfo() {
        return SystemInfo::raw(function($collection) {
            $endTime = intval(microtime(true));
            $startTime = $endTime - (5 * 60);
            return $collection->aggregate([
                ['$match' => ['Time' => ['$gte' => $startTime, '$lte' => $endTime]]],
                ['$group' => ['_id' => '$IPAddress', 'IPAddress' => ['$last' => '$IPAddress'], 'CPUUsage' => ['$avg' => '$CPUUsage'], 'MemoryUsage' => ['$avg' => '$MemoryUsage']]]
            ]);
        });
    }
    
    public function GetProcessStatesByMachine($ip) {
        return SystemInfo::raw(function($collection) use ($ip) {
            $endTime = intval(microtime(true));
            $startTime = $endTime - (10 * 60);
            return $collection->aggregate([
                ['$match' => ['Time' => ['$gte' => $startTime, '$lte' => $endTime], 'IPAddress' => $ip]],
                ['$unwind' => '$ProcessStates'],
                ['$group' => ['_id' => '$ProcessStates.ProcessName', 'CPUUsage' => ['$avg' => '$ProcessStates.CPUUsage'], 'MemoryUsage' => ['$avg' => '$ProcessStates.MemoryUsage']]]
            ]);
        });
    }
}