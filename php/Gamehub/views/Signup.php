<form action="models/signup.php" method="POST">
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
	</table>
	<input type="submit" value="Register" id="Register">
</form>
