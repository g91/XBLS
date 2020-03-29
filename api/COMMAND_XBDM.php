<?php
	require_once 'Config.php';
  	ob_start();
 	$userInfo3 = NULL;
	$uname = "NO";
	$AUTH = 0;

	//?CPUKey={0}&Digest={1}
	$CPUKey = mysqli_real_escape_string($connect, @$_GET['CPUKey']);
	$Digest = mysqli_real_escape_string($connect, @$_GET['Digest']);

	if(isset($CPUKey)) {
		$userQ = @mysqli_query($connect, "SELECT * FROM `clients` WHERE `cpukey` = '" . $CPUKey . "' LIMIT 1");
		if(@mysqli_num_rows($userQ) > 0) {
			$AUTH = 1;
			$userInfo3 = mysqli_fetch_array($userQ);
			$uname = $userInfo3["name"];
		}
	}
	
	mysqli_query($connect, "UPDATE `clients` SET `connect` = connect + 1 WHERE `clients`.`cpukey` = '".$CPUKey."';");
	mysqli_query($connect, "UPDATE `serverstats` SET `variable` = variable + 1 WHERE `serverstats`.`name` = 'connections';");
	if($AUTH == 1){
		echo("TRUE");
	}else{
		echo("false");
	}
?>