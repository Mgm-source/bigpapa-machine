<?php
require_once("../maintenance/config.php");

if (!isset($_SESSION['loggedin'])) {

    if (strtoupper($_SERVER['REQUEST_METHOD']) === 'POST') {

        $username = validinput($_POST['username'], $dbconnect);
        $password = validinput($_POST['password'], $dbconnect);
        $cpassword = validinput($_POST['password2'], $dbconnect);

        if (!verifyPass($password, $cpassword)) {

            redirect("signup");
        }

        if (isUsernameTaken($username, $dbconnect)) {

            redirect("signup");
        }

        $password = encrptpass($password);
        
        if(signup($username, $password, $dbconnect)){
            redirect("signin");
        }
        
    }
    redirect("signup");
} else {

    redirect("home");
}