<?php

if (isset($_SESSION['loggedin'])) {
	header("Location: index.php");
}

?>

<?php if (isset($_GET['msg'])) {

	if ($_GET['msg'] == 'usernametaken') {

		echo "<p><span class=\"warning\">Sorry username already taken<span></p>";
	}
	if ($_GET['msg'] == 'emptypassword') {

		echo "<p>The password field is empty. Please fill. <span class=\"warning\">Spaces are not vaild.<span/></p>";

	}
	if ($_GET['msg'] == 'signupfailed') {

		echo "<p>Sign up failed, <span class=\"warning\">please try again!<span></p>";

	}
	if ($_GET['msg'] == 'passmismatch') {

		echo "<p>Passwords don't match. <span class=\"warning\">Please try again!<span/></p>";

	}
	if ($_GET['msg'] == 'badname') {

		echo "<p>Whitespaces aren't permitted. <span class=\"warning\">Please try again!<span/></p>";

	}
}
?>

<form action="form-handling\signup.php" method="POST">
	<table class="formsignup">
		<tr>
			<td><label for="Username">Username:</label></td>
			<td><input type="text" id="Username" name="username" autocomplete="username" maxlength="20" required></td>
		</tr>
		<tr>
			<td><label for="Password">Password:</label></td>
			<td><input type="password" id="Password" name="password" autocomplete="new-password" maxlength="9"></td>
		</tr>
		<tr>
			<td><label for="Password2">Confirm Password:</label></td>
			<td><input type="password" id="Password2" name="password2" autocomplete="new-password" maxlength="9"></td>
		</tr>

		<tr>
			<td><label for="Register">Sign-up</label></td>
			<td><input type="submit" value="Register" id="Register"></td>
		</tr>
	</table>
</form>