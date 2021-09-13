<?php

// shows user data
if (isset($_SESSION['result'])) {

	foreach($_SESSION['result'] as $result){
		echo $result;
	}
}
?>

<form action="form-handling\account.php">
	<button type="submit">click details</button>
</form>