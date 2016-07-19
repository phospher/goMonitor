<?php 

namespace App\Contracts;

interface SystemInfoRepository {
    
    function GetLast5MinuteSystemInfo();
    
    function GetProcessStatesByMachine($ip);
}