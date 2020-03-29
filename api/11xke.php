<?php
session_start();
require_once 'Config.php';

ob_start();
$userInfo3 = NULL;
$uname = "NO";
$AUTH = 0;

$apikey 			= mysqli_real_escape_string($connect,@$_GET['apikey']);
$hvSalt 			= mysqli_real_escape_string($connect,@$_GET['hvSalt']);
$sessionSalt 		= mysqli_real_escape_string($connect,@$_GET['sessionsalt']);
$cpuKey 			= mysqli_real_escape_string($connect,@$_GET['cpuKey']);
$action 			= mysqli_real_escape_string($connect,@$_GET['action']);
$Type1KV			= mysqli_real_escape_string($connect,@$_GET['Type1']);
$Crl				= mysqli_real_escape_string($connect,@$_GET['CRL']);
$Fcrt				= mysqli_real_escape_string($connect,@$_GET['FCRT']);
$KVCPUKey			= mysqli_real_escape_string($connect,@$_GET['KVCPUKey']);

function handleXeKeysExecute4($HVSalt, $SessionSalt, $CPUKey) 
{
	$url = "http://10.0.0.206:8899/api/XKE/".$CPUKey."/".$HVSalt."/".$SessionSalt."/";
	
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

if (isset($_SERVER["HTTP_CF_CONNECTING_IP"])) 
{
    $_SERVER['REMOTE_ADDR'] = $_SERVER["HTTP_CF_CONNECTING_IP"];
}

function getRandomHex($num_bytes=4) 
{
  return bin2hex(openssl_random_pseudo_bytes($num_bytes));
}

if(isset($apikey)) 
{
	$userQ = @mysqli_query($connect, "SELECT * FROM `clients` WHERE `apikey` = '" . $apikey . "' LIMIT 1");
	if(@mysqli_num_rows($userQ) > 0) 
	{
		$AUTH = 1;
		$userInfo3 = mysqli_fetch_array($userQ);
		$uname = $userInfo3["name"];
		if ($action == "getChallengeCertificate"){
			echo handleXeKeysExecute4($hvSalt, $sessionSalt, $cpuKey);
		}
	}
}
exit();
?>