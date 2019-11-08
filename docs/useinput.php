<?php
include 'function.php';
?>
<form action="useinput.php" method="POST">

<label for="Username">Username</label>
<input type="text" name="Username" id="Username">
<label for="Password">Password</label>
<input type="password" name="Password" id="Password">

<input type="submit" value="Register">
</form>
<?php
$username="";

$password="";

if(isset($_POST['Username']) && $_POST['Password'])
{
$username = $_POST['Username']; 
$password = $_POST['Password']; 

echo "Your Username is ".$username."<br>"." Your Password is ".$password;
}
else
	
echo ""; 
?>