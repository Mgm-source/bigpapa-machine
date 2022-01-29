<?php
require_once '../maintenance/config.php';
require_once '../misc/helper.php';


if (isset($_SESSION['loggedin'])) {

	if (!$dbconnect) {

		die("500 Internal Server Error " . mysqli_connect_error());
	}

	if($_GET['page']=='record'){

	}

	if($_GET['page']=='leaderboard'){

	}
}


mysqli_close($dbconnect);
