<?php
require_once("../maintenance/config.php");

if (!isset($_SESSION['loggedin'])) {

    if (strtoupper($_SERVER['REQUEST_METHOD']) === 'POST') {

        $username = validinput($_POST['username'], $dbconnect);
        $password = validinput($_POST['password'], $dbconnect);
        $cpassword = validinput($_POST['password2'], $dbconnect);

        if (!verifyPass($password, $cpassword)) {

            redirect("../views/signup.php");
        }

        if (isUsernameTaken($username, $dbconnect)) {

            redirect("../views/signup.php");
        }

        $password = encrptpass($password);
        signup($username, $password, $dbconnect);
    }
    redirect("../views/signup.php");
} else {

    redirect("../index.php");
}

mysqli_close($dbconnect);
