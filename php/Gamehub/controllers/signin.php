<?php

require_once("../maintenance/config.php");

if (!isset($_SESSION['loggedin'])) {

    if (!$dbconnect) {

        die("500 Internal Server Error " . mysqli_connect_error());
    }

    if (strtoupper($_SERVER['REQUEST_METHOD']) === 'POST') {

        $username = validinput($_POST['username'], $dbconnect);
        $password = validinput($_POST['password'], $dbconnect);
        $password = encrptpass($password);

        if (signin($username, $password,$dbconnect)) {
            redirect("../index.php");
        }
    }

    redirect("../views/signin.php");
} else {

    signout();
    redirect("../index.php");
}

mysqli_close($dbconnect);
