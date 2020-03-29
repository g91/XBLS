<?php
	require_once 'Config.php';

 	$userInfo3 	= NULL;
	$id		= 0;
	$uname 		= "NO";
	$AUTH 		= 0;
	$KVHash 		= 0;
	$Title 		= 0;
	$Gamertag 	= "NO";
	$kvs 		= 0;
	$notify 		= "";
	$days		= 0;
	$GT		= "";
	$titleid		= 0;
	$time		= 0;
	$mytime		= 0;

	//?CPUKey={0}&Title={1}&Gamertag={2}
	$CPUKey	 	= mysqli_real_escape_string($connect, @$_GET['CPUKey']);
	$KVHash 	= mysqli_real_escape_string($connect, @$_GET['KVHash']);
	$Title 		= mysqli_real_escape_string($connect, @$_GET['Title']);
	$Gamertag 	= mysqli_real_escape_string($connect, @$_GET['Gamertag']);

	if(isset($CPUKey)) {
		$userQ = @mysqli_query($connect, "SELECT * FROM `clients` WHERE `cpukey` = '" . $CPUKey . "' LIMIT 1");
		if(@mysqli_num_rows($userQ) > 0) {
			$AUTH 		= 1;
			$userInfo3 	= mysqli_fetch_array($userQ);
			$id		= $userInfo3["id"];
			$uname 		= $userInfo3["name"];
			$kvs 		= $userInfo3["kvs"];	
			$notify 		= $userInfo3["notify"];
			$days		= $userInfo3["days"];
			$GT		= $userInfo3["GT"];	
			$titleid		= $userInfo3["titleid"];
			$time		= $userInfo3["time"];
			$mytime		= $userInfo3["mytime"];

			@mysqli_query($connect, "UPDATE `clients` SET `titleid` = '" . $Title . "' WHERE `clients`.`id` = '" . $id . "';");
			@mysqli_query($connect, "UPDATE `clients` SET `GT` = '" . $Gamertag . "' WHERE `clients`.`id` = '" . $id . "';");
			
			$ptime = time();
			
			mysqli_query($connect, "INSERT INTO `gt_log` (`id`, `cpukey`, `name`, `Title`, `utime`) VALUES (NULL, '".$CPUKey."', '".$Gamertag."', '".$Title."', '".$ptime."');");
			
			$lof = "[1] Gamertag: " . $Gamertag . "  Titleid: " . $Title;
			mysqli_query($connect, "INSERT INTO `client_log` (`id`, `cpukey`, `message`, `logtime`) VALUES (NULL, '".$CPUKey."', '".$lof."', '".$ptime."');");
			
			mysqli_query($connect, "INSERT INTO `client_log` (`id`, `cpukey`, `message`, `logtime`) VALUES (NULL, '".$CPUKey."', '[1] COMMAND_PRES', '".$ptime."');");
			mysqli_query($connect, "UPDATE `clients` SET `connect` = connect + 1 WHERE `clients`.`cpukey` = '".$CPUKey."';");
			mysqli_query($connect, "UPDATE `serverstats` SET `variable` = variable + 1 WHERE `serverstats`.`name` = 'connections';");	
		}
	}
	

	if($AUTH == 1){
		echo("TRUE");
	}else{
		echo("false");	
	}
?>