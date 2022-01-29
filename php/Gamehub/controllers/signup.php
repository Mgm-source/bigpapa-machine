<?php
require_once '../maintenance/config.php';
require_once '../misc/helper.php'; 

if (!isset($_SESSION['loggedin'])) {

    if (!$dbconnect) {

        die("500 Internal Server Error" . $dbconnect_connect_error);
    }


    if (strtoupper($_SERVER['REQUEST_METHOD']) === 'POST') {

        $username = validinput($_POST['username'], $dbconnect);
        $password = validinput($_POST['password'], $dbconnect);
        $cpassword = validinput($_POST['password2'], $dbconnect);
        
        if(!verifyPass($password, $cpassword)){

            redirect("../views/signup.php");

        }
        
        if(isUsernameTaken($username)){

            redirect("../views/signup.php");
        }

        $password = encrptpass($password);
        signup($username,$password);

    }
    redirect("../views/signup.php");

}else {

    redirect("../index.php");

} 

mysqli_close($dbconnect);