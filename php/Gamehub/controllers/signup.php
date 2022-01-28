<?php
if (isset($_POST['username'])) {

    if (!$dbconnect) {

        die("Connection Failed: " . $dbconnect_connect_error);
    }
    if (strtoupper($_SERVER['REQUEST_METHOD']) === 'POST') {

        $username = validinput($_POST['username'], $dbconnect);
        $password = validinput($_POST['password'], $dbconnect);
        $cpassword = validinput($_POST['password2'], $dbconnect);

        if (!Charspace($username)) {
            if (verifyPass($password, $cpassword)) {
                if (!emptyPass($password, $dbconnect)) {

                    $password = encrptpass($password);

                    $query = "SELECT 'username' FROM users WHERE username = '$username';";
                    $result = mysqli_query($dbconnect, $query);

                    if (mysqli_num_rows($result) > 0) {
                        
                    } 
                    
                    else {

                        $query = "INSERT INTO users (username, password) VALUES ('$username', '$password');";
                        $result = mysqli_query($dbconnect, $query);

                        if ($result) {
                            
                        } 
                    }
                }
            }
        }
    }
    mysqli_close($dbconnect);
}
