<?php

// shows user data
if (isset($_SESSION['loggedin'])) {

	$username = $_SESSION["username"];

	if (!$dbconnect) {

		die("Connection Failed: " . mysqli_connect_error());
		
	} else {

		$query = "SELECT * FROM record left join user ON record.username = users.username WHERE user.username = '$username'";
		$result = mysqli_query($dbconnect, $query);

		if (mysqli_num_rows($result) > 0) {

			$_SESSION['result'] = mysqli_fetch_assoc($result);

		} 

	}

	mysqli_close($dbconnect);
}
