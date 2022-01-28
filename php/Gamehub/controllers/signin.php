<?php

if (isset($_POST['username'])) {

    if (!$dbconnect) {

        die("Connection Failed: " . mysqli_connect_error());
    }
    if (strtoupper($_SERVER['REQUEST_METHOD']) === 'POST') {

        $username = validinput($_POST['username'], $dbconnect);
        $password = validinput($_POST['password'], $dbconnect);
    }

    if (!emptyPass($password)) {

        $password = encrptpass($password);

        $query = "SELECT username, password FROM user WHERE username = '$username' AND password = '$password'";
        $result = mysqli_query($dbconnect, $query);

        if (mysqli_num_rows($result) > 0) {

            $_SESSION['loggedin'] = true;
            $_SESSION['username'] = $username;
            
        } 

    } 

    mysqli_close($dbconnect);

}
