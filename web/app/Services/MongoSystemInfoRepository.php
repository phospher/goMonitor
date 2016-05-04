<?php 

namespace App\Services;

use App\Contracts\SystemInfoRepository;
use App\SystemInfo;

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

}