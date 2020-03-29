<?php
	require_once 'Config.php';

 	$userInfo3 	= NULL;
	$uname 		= "NO";
	$AUTH 		= 0;
	$KVHash 	= 0;
	$Title 		= 0;
	$Gamertag 	= "NO";
	$kvs 		= 0;
	$notify 	= "";
	$days		= 0;
	$GT			= "";
	$titleid	= 0;
	$time		= 0;
	$mytime		= 0;

	//?CPUKey={0}&Salt={1}&KVCPUKey={2}&KVSignature={3}&response={4}&test=1
	$CPUKey 		= mysqli_real_escape_string($connect, @$_GET['CPUKey']);
	$KVHash 		= mysqli_real_escape_string($connect, @$_GET['KVHash']);
	$KVCPUKey 		= mysqli_real_escape_string($connect, @$_GET['KVCPUKey']);
	$KVSignature 	= mysqli_real_escape_string($connect, @$_GET['KVSignature']);
	$Response 		= mysqli_real_escape_string($connect, @$_GET['response']);
	$test 			= mysqli_real_escape_string($connect, @$_GET['test']);
	
	if(isset($CPUKey)) {
		$userQ = @mysqli_query($connect, "SELECT * FROM `clients` WHERE `cpukey` = '" . $CPUKey . "' LIMIT 1");
		if(@mysqli_num_rows($userQ) > 0) {
			$AUTH 		= 1;
			$userInfo3 	= mysqli_fetch_array($userQ);
			$uname 		= $userInfo3["name"];
			$kvs 		= $userInfo3["kvs"];	
			$notify 	= $userInfo3["notify"];
			$days		= $userInfo3["days"];
			$Gamertag	= $userInfo3["Gamertag"];	
			$titleid	= $userInfo3["titleid"];
			$yourtime	= $userInfo3["time"];
			$mytime		= $userInfo3["mytime"];
		}
	}


	$ptime = time();
	mysqli_query($connect, "INSERT INTO `client_log` (`id`, `cpukey`, `message`, `logtime`) VALUES (NULL, '".$CPUKey."', '[1] COMMAND_XKEC', '".$ptime."');");
	mysqli_query($connect, "UPDATE `clients` SET `challenges` = challenges + 1 WHERE `clients`.`cpukey` = '".$CPUKey."';");
	mysqli_query($connect, "UPDATE `clients` SET `connect` = connect + 1 WHERE `clients`.`cpukey` = '".$CPUKey."';");
	mysqli_query($connect, "UPDATE `serverstats` SET `variable` = variable + 1 WHERE `serverstats`.`name` = 'connections';");
	mysqli_query($connect, "UPDATE `serverstats` SET `variable` = variable + 1 WHERE `serverstats`.`name` = 'challenges';");
	mysqli_query($connect, "INSERT INTO `xkex_log` (`id`, `CPUKey`, `KVHash`, `KVCPUKey`, `KVSignature`, `response`, `test`)  VALUES (NULL, '".$CPUKey."', '".$KVHash."', '".$KVCPUKey."', '".$KVSignature."', '".$Response."', '".$test."');");


	if($AUTH == 1){
		echo("TRUE");
	}else{
		echo("false");
	}
?>