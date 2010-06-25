<?php
ini_set("display_errors", 0);
date_default_timezone_set('UTC');

define("DATE_FORMAT", "l, F jS");
define("TIME_FORMAT", "g:ia");
define("LIFESTART","1987-05-21 00:00:00");
define("ANCILLARY_FORMAT", "Y-W-z");

function stillAlive(){
    $f = new DateTime();
    $t = new DateTime(LIFESTART);
    $res = date_diff($f, $t);
    return $res->format("%a")+1;
}

function meminfo($type){
    switch($type){
    case "total":
        $key = "MemTotal";
        break;
    case "free":
        $key = "Inactive";
        break;
    case "used":
        $key = "Active";
        break;
    case "swap-total":
        $key = "SwapTotal";
        break;
    case "swap-free":
        $key = "SwapFree";
        break;
    case "swap-used":
        return meminfo("swap-total")-meminfo("swap-free");
            
    default:
        $key = "MemTotal";
    }
    
    $val = trim(shell_exec("cat /proc/meminfo | grep \"^$key:\" | tr -s ' ' | cut -d' ' -f2"));
    if(is_numeric($val))
        return number_format($val/(1024*1024),2);
    return 0;
}

?>
<html>
    <head>
        <title />
        <link rel="stylesheet" type="text/css" href="main.css" />
    </head>
    <body>
        <div id="root">
            <div class="section temporal">
                <span class="date"><?php echo date(DATE_FORMAT) ?></span>
                <span class="time"><?php echo date(TIME_FORMAT) ?></span>
                <span class="stillAlive">Day <?php echo stillAlive() ?></span>
                <span class="ancillary"><?php echo date(ANCILLARY_FORMAT) ?></span>
            </div>
            
            <div class="section sysinfo">
                <h1>Panel</h1>
                <div class="data-table">
                    <span>
                        <label>Host</label>
                        <span><?php echo shell_exec("hostname"); ?></span>
                    </span>
                    
                    <span>
                        <label>Uptime</label>
                        <span><?php echo date("z\d G\h i\m", shell_exec("cat /proc/uptime | cut -f1 -d'.'")) ?></span>
                    </span>
                    
                    <span>
                        <label>Load</label>
                        <span><?php echo trim(shell_exec("uptime | cut -d: -f5")); ?></span>
                    </span>
                    
                    <span>
                        <label>Temperature</label>
                        <span>--C</span>
                    </span>
                    
                    <span>
                        <label>RAM</label>
                        <span><?php echo meminfo("used")."GiB/".meminfo("total")."GiB" ?></span>
                    </span>
                    
                    <span>
                        <label>Swap</label>
                        <span><?php echo meminfo("swap-used")."GiB/".meminfo("swap-total")."GiB" ?></span>
                    </span>
                </div>
            </div>
        </div>
    </body>
</html>
