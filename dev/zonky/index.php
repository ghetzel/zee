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


$d = array();

$d["date"] 			= date(DATE_FORMAT);
$d["time"] 			= date(TIME_FORMAT);
$d["still-alive"]		= stillAlive();
$d["ancillary"]			= date(ANCILLARY_FORMAT);
$d["hostname"]			= shell_exec("hostname");
$d["uptime"]			= date("z\d G\h i\m", shell_exec("cat /proc/uptime | cut -f1 -d'.'"));
$d["load"]			= trim(shell_exec("uptime | cut -d: -f5"));
$d["temperature"]["mb"]		= trim(shell_exec("cat /proc/acpi/thermal_zone/TZ00/temperature | tr -s ' ' | cut -d' ' -f2"));
$d["memory"]["system"]["free"]	= meminfo("free");
$d["memory"]["system"]["used"]	= meminfo("used");
$d["memory"]["system"]["total"]	= meminfo("total");
$d["memory"]["swap"]["free"]	= meminfo("swap-free");
$d["memory"]["swap"]["used"]	= meminfo("swap-used");
$d["memory"]["swap"]["total"]	= meminfo("swap-total");

?>
<html>
    <head>
        <title />
        <link rel="stylesheet" type="text/css" href="main.css" />
	<script type="text/javascript" src="mootools-1.2.4-core.js"></script>
    </head>
    <body>
	<script type="text/javascript">
		window.addEvent('domready', function(){
			var reloader = function(){ window.location.reload(); };
			reloader.periodical(1000*60);
		});
	</script>
        <div id="root">
            <div class="section temporal">
		<div class="data-table">
			<span>
		                <span class="date"><?php echo $d["date"] ?></span>
        		        <span class="time"><?php echo $d["time"] ?></span>
			</span>
			<span>
	                	<span class="stillAlive">Day <?php echo $d["still-alive"] ?></span>
		                <span class="ancillary"><?php echo $d["ancillary"] ?></span>
			</span>
		</div>
            </div>
            
            <div class="section sysinfo">
                <h1>Doo Panel</h1>
                <div class="data-table">
                    <span>
                        <label>Host</label>
                        <span><?php echo $d["hostname"] ?></span>
                    </span>
                    
                    <span>
                        <label>Uptime</label>
                        <span><?php echo $d["uptime"] ?></span>
                    </span>
                    
                    <span>
                        <label>Load</label>
                        <span><?php echo $d["load"] ?></span>
                    </span>
                    
                    <span>
                        <label>Temperature</label>
                        <span><?php echo $d["temperature"]["mb"] ?>&deg;C</span>
                    </span>
                    
                    <span>
                        <label>RAM</label>
                        <span><?php echo $d["memory"]["system"]["used"]."GiB/".$d["memory"]["system"]["total"]."GiB" ?></span>
                    </span>
                    
                    <span>
                        <label>Swap</label>
                        <span><?php echo $d["memory"]["swap"]["used"]."GiB/".$d["memory"]["swap"]["total"]."GiB" ?></span>
                    </span>
                </div>
            </div>
        </div>
    </body>
</html>
