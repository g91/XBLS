<?php
	//===============================================================
	session_start();
	require_once 'Config.php';
	//===============================================================
	ob_start();
	$userInfo3 = NULL;
	$uname = "NO";
	$AUTH = 0;
	//===============================================================
	$apikey 			= mysqli_real_escape_string($connect,@$_GET['apikey']);
	$hvSalt 			= mysqli_real_escape_string($connect,@$_GET['hvSalt']);
	$sessionSalt 		= mysqli_real_escape_string($connect,@$_GET['sessionsalt']);
	$cpuKey 			= mysqli_real_escape_string($connect,@$_GET['cpuKey']);
	$action 			= mysqli_real_escape_string($connect,@$_GET['action']);
	$Type1KV			= mysqli_real_escape_string($connect,@$_GET['Type1']);
	$Crl				= mysqli_real_escape_string($connect,@$_GET['CRL']);
	$Fcrt				= mysqli_real_escape_string($connect,@$_GET['FCRT']);
	$KVCPUKey			= mysqli_real_escape_string($connect,@$_GET['KVCPUKey']);
	//===============================================================
	$Title 				= mysqli_real_escape_string($connect,@$_GET['Title']); 
	$KVDigest			= mysqli_real_escape_string($connect,@$_GET['KVDigest']);
	$spoofedMacAddress	= mysqli_real_escape_string($connect,@$_GET['spoofedMacAddress']); 
	$SerialByte			= mysqli_real_escape_string($connect,@$_GET['SerialByte']);
	//===============================================================
	function handleCurl($url)
	{
		// create curl resource
		$ch = curl_init();

		// set url
		curl_setopt($ch, CURLOPT_URL, $url);

		//return the transfer as a string
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);

		// $output contains the output string
		$output = curl_exec($ch);

		// close curl resource to free up system resources
		curl_close($ch);  
		
		return $output;
	}
	//===============================================================
	function handleFuseExecute($KVDigest, $SerialByte) 
	{
		return handleCurl("http://74.91.112.229:8899/api/Fuse/" . $KVDigest . "/" . $SerialByte . "/");
	}
	//===============================================================
	function handleTitleExecute($Title, $KVDigest, $spoofedMacAddress, $SerialByte) 
	{
		return handleCurl("http://74.91.112.229:8899/api/Title/" . $Title . "/" . $KVDigest . "/" . $spoofedMacAddress . "/" . $SerialByte . "/");
	}
	//===============================================================
	function handleXeKeysExecute4($HVSalt, $SessionSalt, $CPUKey) 
	{
		return handleCurl("http://74.91.112.229:8899/api/XKE/" . $CPUKey . "/" . $HVSalt . "/" . $SessionSalt . "/");
	}
	//===============================================================
	if (isset($_SERVER["HTTP_CF_CONNECTING_IP"])) 
	{
		$_SERVER['REMOTE_ADDR'] = $_SERVER["HTTP_CF_CONNECTING_IP"];
	}
	//===============================================================
	$ip = $_SERVER['REMOTE_ADDR'];
	//===============================================================
	if(isset($apikey)) 
	{
		//===============================================================
		$userQ = @mysqli_query($connect, "SELECT * FROM `clients` WHERE `apikey` = '" . $apikey . "' LIMIT 1");
		if(@mysqli_num_rows($userQ) > 0) 
		{
			//===============================================================
			@mysqli_query($connect,"INSERT INTO `api_log` (`id`, `apikey`, `hvSalt`, `sessionSalt`, `cpuKey`, `ip`, `action`, `Type1KV`, `Crl`, `Fcrt`, `KVCPUKey`, `Title`, `KVDigest`, `spoofedMacAddress`, `SerialByte`) VALUES (NULL, '".$apikey."', '".$hvSalt."', '".$sessionSalt."', '".$cpuKey."', '".$ip."', '".$action."', '".$Type1KV."', '".$Crl."', '".$Fcrt."', '".$KVCPUKey."', '".$Title."', '".$KVDigest."', '".$spoofedMacAddress."', '".$SerialByte."')");
			//===============================================================
			$AUTH = 1;
			$userInfo3 = mysqli_fetch_array($userQ);
			$uname = $userInfo3["name"];
			if ($action == "getChallengeCertificate")
			{
				echo handleXeKeysExecute4($hvSalt, $sessionSalt, $cpuKey);
			}
		}
		//===============================================================
		if ($action == "getTitleDigest")
		{
			//===============================================================
			@mysqli_query($connect,"INSERT INTO `api_log` (`id`, `apikey`, `hvSalt`, `sessionSalt`, `cpuKey`, `ip`, `action`, `Type1KV`, `Crl`, `Fcrt`, `KVCPUKey`, `Title`, `KVDigest`, `spoofedMacAddress`, `SerialByte`) VALUES (NULL, '".$apikey."', '".$hvSalt."', '".$sessionSalt."', '".$cpuKey."', '".$ip."', '".$action."', '".$Type1KV."', '".$Crl."', '".$Fcrt."', '".$KVCPUKey."', '".$Title."', '".$KVDigest."', '".$spoofedMacAddress."', '".$SerialByte."')");
			//===============================================================
			echo handleTitleExecute($Title, $KVDigest, $spoofedMacAddress, $SerialByte) ;
		}
		//===============================================================
		if ($action == "getFuseDigest")
		{
			//===============================================================
			@mysqli_query($connect,"INSERT INTO `api_log` (`id`, `apikey`, `hvSalt`, `sessionSalt`, `cpuKey`, `ip`, `action`, `Type1KV`, `Crl`, `Fcrt`, `KVCPUKey`, `Title`, `KVDigest`, `spoofedMacAddress`, `SerialByte`) VALUES (NULL, '".$apikey."', '".$hvSalt."', '".$sessionSalt."', '".$cpuKey."', '".$ip."', '".$action."', '".$Type1KV."', '".$Crl."', '".$Fcrt."', '".$KVCPUKey."', '".$Title."', '".$KVDigest."', '".$spoofedMacAddress."', '".$SerialByte."')");
			//===============================================================
			echo handleFuseExecute($KVDigest, $SerialByte) ;
		}
		//===============================================================
	}
	//===============================================================
	exit();
?>