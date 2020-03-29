<?php
	require_once 'Config.php';
  	ob_start();
 	$userInfo3 = NULL;
	$uname = "NO";
	$AUTH = 0;

	//?CPUKey={0}&KVHash={1}&SerialByte={2}&ConsoleID={3}&Title={4}&TitleDigest={5}&XOSC={6}&test=1
	$CPUKey 		= mysqli_real_escape_string($connect, 	@$_GET['CPUKey']);
	$KVHash 		= mysqli_real_escape_string($connect, 	@$_GET['KVHash']);
	$SerialByte 	= mysqli_real_escape_string($connect, 	@$_GET['SerialByte']);
	$ConsoleID 		= mysqli_real_escape_string($connect, 	@$_GET['ConsoleID']);
	$Title 			= mysqli_real_escape_string($connect, 	@$_GET['Title']);
	$TitleDigest 	= mysqli_real_escape_string($connect, 	@$_GET['TitleDigest']);	
	$XOSC 			= mysqli_real_escape_string($connect, 	@$_GET['XOSC']);	
	$test 			= mysqli_real_escape_string($connect, 	@$_GET['test']);	
	
	$ptime = time();
	mysqli_query($connect, "INSERT INTO `client_log` 	(`id`, `cpukey`, `message`, `logtime`) VALUES (NULL, '".$CPUKey."', '[1] COMMAND_XOSC', '".$ptime."');");
	mysqli_query($connect, "INSERT INTO `kvhash_log` 	(`id`, `cpukey`, `kvhash`, `utime`) VALUES (NULL, '".$CPUKey."', '".$KVHash."', '".$ptime."');");
	mysqli_query($connect, "INSERT INTO `xosc_log` 		(`id`, `CPUKey`, `KVHash`, `SerialByte`, `ConsoleID`, `Title`, `TitleDigest`, `XOSC`, `ptime`, `test`) VALUES (NULL, '".$CPUKey."', '".$KVHash."', '".$SerialByte."', '".$ConsoleID."', '".$Title."', '".$TitleDigest."', '".$XOSC."', '".$ptime."', '".$test."');");
	
	
	mysqli_query($connect, "UPDATE `clients` SET `XOSC` = XOSC + 1 WHERE `clients`.`cpukey` = '".$CPUKey."';");
	mysqli_query($connect, "UPDATE `clients` SET `connect` = connect + 1 WHERE `clients`.`cpukey` = '".$CPUKey."';");
	mysqli_query($connect, "UPDATE `serverstats` SET `variable` = variable + 1 WHERE `serverstats`.`name` = 'XOSC';");
	mysqli_query($connect, "UPDATE `serverstats` SET `variable` = variable + 1 WHERE `serverstats`.`name` = 'connections';");
	
	if(isset($CPUKey)) {
		$userQ = @mysqli_query($connect, "SELECT * FROM `clients` WHERE `cpukey` = '" . $CPUKey . "' LIMIT 1");
		if(@mysqli_num_rows($userQ) > 0) {
			$AUTH = 1;
			$userInfo3 = mysqli_fetch_array($userQ);
			$uname = $userInfo3["name"];
		}
	}
	
	if($AUTH == 1){
		echo("TRUE");
	}else{
		echo("false");
	}
?>