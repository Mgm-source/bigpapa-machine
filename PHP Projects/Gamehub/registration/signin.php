<?php
if (isset($_SESSION['loggedin'])) {
    header("Location: index.php");
}
?>

<?php if (isset($_GET['msg'])) {

    if ($_GET['msg'] == 'SigninFailure') {
    
        echo "<p>Your Sign in attempt failed. <span class=\"warning\">Either your password or username was incorrect.<span/></p>";
    }
    if ($_GET['msg'] == 'emptypassword') {
    
        echo "<p>The password field is empty. Please fill. <span class=\"warning\">Spaces are not vaild.<span/></p>";

    }
    if ($_GET['msg'] == 'signin') {
    
        echo "<p>You must be logged. <span class=\"warning\">To view this page.<span/></p>";

    }
} 
?>

<form action="form-handling\signin.php" method="POST">
    <table class="formSignin">
        <tr>
            <td><label for="Username">Username:</label></td>
            <td><input type="text" id="Username" name="username" autocomplete="username" required></td>
        </tr>
        <tr>
            <td><label for="Password">Password:</label></td>
            <td><input type="password" id="Password" name="password" autocomplete="password" required></td>
        </tr>
        <tr>
            <td><input type="submit" value="Sign in" id="Register"></td>
        </tr>
    </table>
</form>