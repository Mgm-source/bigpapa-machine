<?php
    require_once("../maintenance/config.php");
	
if (isset($_SESSION['loggedin'])) {

	if (!$dbconnect) {

		die("500 Internal Server Error " . mysqli_connect_error());
	}
	
}


mysqli_close($dbconnect);
