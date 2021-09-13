<?php

require_once '..\maintenance\config.php';

// shows user data
if (isset($_SESSION['loggedin'])) {

	$username = $_SESSION["username"];

	if (!$dbconnect) {

		die("Connection Failed: " . mysqli_connect_error());
		
	} else {

		$query = "SELECT player_nickname, player_score FROM players LEFT JOIN users ON players.player_id = users.username WHERE users.username = '$username'";
		$result = mysqli_query($dbconnect, $query);

		if (mysqli_num_rows($result) > 0) {

			$_SESSION['result'] = mysqli_fetch_assoc($result);

		} else {

			unset($_SESSION['result']);

		}

		header("Location: $home/index.php?page=Account");
	}
} else {

	header("Location: $home/index.php?msg=signin&page=signin");

}
