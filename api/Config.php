<?php
	//============================================================
	$_MySQL['host'] = '127.0.0.1';
	$_MySQL['username'] = 'root';
	$_MySQL['password'] = 'LIC#20998';
	$_MySQL['database'] = 'evilsource_xblapi';
	//============================================================
	$connect = mysqli_connect($_MySQL['host'], $_MySQL['username'], $_MySQL['password']) or die("Could not connect: " . mysqli_error());
	mysqli_select_db($connect, $_MySQL['database']);
	//============================================================
?>
