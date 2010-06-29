<?php
ini_set("display_errors", 0);
date_default_timezone_set('EDT');

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
		return $val*1024;
	return 0;
}

function szexp($abbr,$val=NULL){
	if($abbr == "auto" && $val){
		if($val < 1024)								    // bytes
			return szexp("B");
		else if($val < 1048576)						    // KB
			return szexp("K");
		else if($val < 1073741824)						// MB
			return szexp("M");
		else if($val < 1099511627776)					// GB
			return szexp("G");
		else if($val < 1125899906842624)				// TB
			return szexp("T");
		else if($val < 1152921504606846976)			    // PB
			return szexp("P");
		else if($val < 1180591620717411303424)			// EB
			return szexp("E");
		else if($val < 1208925819614629174706176)		// ZB
			return szexp("Z");
		else if($val < 1237940039285380274899124224)	// YB
			return szexp("Y");
		else
			return szexp("B");
	}else{
		switch($abbr){
		case "B":	// bytes
			return 0;
		case "K":	// kilobytes
			return 1;
		case "M":	// megabytes
			return 2;
		case "G":	// gigabytes
			return 3;
		case "T":	// terabytes
			return 4;
		case "P":	// petabytes
			return 5;
		case "E":	// exabytes
			return 6;
		case "Z":	// zettabytes
			return 7;
		case "Y":	// yottabytes
			return 8;
		default:
			return 0;
		}		
	}
}


function szunit($exp){
	switch($exp){
	case 0:	// bytes
		return "B";
	case 1:	// kilobytes
		return "KiB";
	case 2:	// megabytes
		return "MiB";
	case 3:	// gigabytes
		return "GiB";
	case 4:	// terabytes
		return "TiB";
	case 5:	// petabytes
		return "PiB";
	case 6:	// exabytes
		return "EiB";
	case 7:	// zettabytes
		return "ZiB";
	case 8:	// yottabytes
		return "YiB";
	default:
		return "";
	}
}



function szconv($val, $to="auto", $from="B"){
	if(trim($from) == "" || trim($to) == "")
		return "*";

	$fexp = szexp($from,$val);
	$texp = szexp($to,$val);
	$unit = szunit($texp);
	
	if($val < 0)
		$val = 0;
	
	if($fexp == $texp)
		$rv = $val;
	else if($texp < $fexp)
		$rv = ($val*pow(1024.0,$fexp-$texp));
	else
		$rv = ($val/pow(1024.0,$texp-$fexp));
		
	switch($texp){
	case 0: // B
	case 1: // K
		break;
	case 2: // M
		$rv = round($rv,1);
		break;
	case 3: // G
	case 4: // T
		$rv = round($rv,2);
		break;
	default:
		$rv = round($rv,3);
		break;		
	}
	
	return $rv.$unit;
}

$d = array();

$d["date"] 			            = date(DATE_FORMAT);
$d["time"] 			            = date(TIME_FORMAT);
$d["still-alive"]		        = stillAlive();
$d["ancillary"]			        = date(ANCILLARY_FORMAT);
$d["hostname"]			        = shell_exec("hostname");
$d["uptime"]			        = date("z\d G\h i\m", shell_exec("cat /proc/uptime | cut -f1 -d'.'"));
$d["load"]			            = trim(shell_exec("uptime | grep -o 'load average:.*' | cut -d: -f2"));
$d["temperature"]["mb"]		    = trim(shell_exec("cat /proc/acpi/thermal_zone/THM/temperature | tr -s ' ' | cut -d' ' -f2"));
$d["memory"]["system"]["free"]	= meminfo("free");
$d["memory"]["system"]["used"]	= meminfo("used");
$d["memory"]["system"]["total"]	= meminfo("total");
$d["memory"]["swap"]["free"]	= meminfo("swap-free");
$d["memory"]["swap"]["used"]	= meminfo("swap-used");
$d["memory"]["swap"]["total"]	= meminfo("swap-total");

// processor
$tmp = shell_exec("mpstat -P ALL | tr -s ' ' | grep -vE 'Linux|CPU|all|^$'");
$tmp = explode("\n", $tmp);

if(is_array($tmp)){
	foreach($tmp as $i){
		if($i == "")
			continue;

		$t = explode(" ", $i);
		$d["processor"][$t[1]]["user"] = $t[2];
		$d["processor"][$t[1]]["nice"] = $t[3];
		$d["processor"][$t[1]]["system"] = $t[4];
		$d["processor"][$t[1]]["iowait"] = $t[5];		
		$d["processor"][$t[1]]["idle"] = $t[count($t)-1];
		$d["processor"][$t[1]]["total"] = $t[2]+$t[3]+$t[4]+$t[5];
	}
}

// mounts / disks
$tmp = shell_exec("df -B1 | grep -vE '^Filesystem|shm' | tr -s ' ' | cut -d' ' -f1,2,3,4,6");
$tmp = explode("\n", $tmp);

if(is_array($tmp)){
	foreach($tmp as $i){
		if($i == "")
			continue;
			
		$t = explode(" ", $i);
		$d["disks"][$t[4]]["device"] = $t[0];
		$d["disks"][$t[4]]["total"] = $t[1];
		$d["disks"][$t[4]]["used"] = $t[2];
		$d["disks"][$t[4]]["free"] = $t[3];		
	}
}

// network
$tmp = shell_exec("cat /proc/net/dev | grep '^[ ]\+[A-Za-z0-9]*:' | sed 's/:[ ]\?/ /' | tr -s ' '");
$tmp = explode("\n", $tmp);

if(is_array($tmp)){
	foreach($tmp as $i){
		if($i == "")
			continue;
	
		$t = explode(" ", trim($i));
		$d["network"]["interfaces"][$t[0]]["hwaddr"] = shell_exec("ifconfig $t[0] | grep -o '[0-9A-F:]\{17\}'");
		$d["network"]["interfaces"][$t[0]]["address"] = shell_exec("ifconfig $t[0] | grep -o 'inet addr:\([0-9.]\+\)' | cut -d: -f2");
		$d["network"]["interfaces"][$t[0]]["broadcast"] = shell_exec("ifconfig $t[0] | grep -o 'Bcast:\([0-9.]\+\)' | cut -d: -f2");
		$d["network"]["interfaces"][$t[0]]["netmask"] = shell_exec("ifconfig $t[0] | grep -o 'Mask:\([0-9.]\+\)' | cut -d: -f2");		
		$d["network"]["interfaces"][$t[0]]["in"] = $t[1];
		$d["network"]["interfaces"][$t[0]]["out"] = $t[9];
	}
}
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
			reloader.periodical(3000);
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
						<span><?php echo szconv($d["memory"]["system"]["used"])." / ".szconv($d["memory"]["system"]["total"]) ?></span>
					</span>
					
					<span>
						<label>Swap</label>
						<span><?php echo szconv($d["memory"]["swap"]["used"])." / ".szconv($d["memory"]["swap"]["total"]) ?></span>
					</span>
					
					<span>
					    <label>CPU Usage:</label>
				    <?php foreach($d["processor"] as $cpu => $info): ?>
				        <span><?php echo $cpu.": ".$info["user"]."% " ?></span>
				    <?php endforeach; ?>
					</span>
				</div>
			</div>
			
			<div class="section mounts">
				<h1>Mounts</h1>
				<div class="data-table">
				<?php foreach($d["disks"] as $mountpoint => $info): ?>
					<span>
						<label><?php echo $mountpoint ?></label>
						<span><?php echo szconv($info["free"]) ?> free</span>
						<span><?php echo szconv($info["total"]) ?></span>						
					</span>
				<?php endforeach; ?>
				</div>
			</div>
			
			<div class="section network">
				<h1>Network</h1>
				<div class="data-table">
				<?php foreach($d["network"]["interfaces"] as $netif => $info): ?>
				    <?php if(!$info["address"]) continue; ?>
					<span>
						<label><?php echo $netif ?></label>
						<span><?php echo $info["address"] ?></span>
						<!--<span><?php echo $info["out"] ?> / <?php echo $info["in"] ?></span>-->
					</span>
				<?php endforeach; ?>
				</div>
			</div>			
		</div>
	</body>
</html>
