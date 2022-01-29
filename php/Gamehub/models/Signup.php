<?php

    require_once("../controllers/signup.php");

    function signup($username,$password){

            $query = "INSERT INTO user VALUES ('$username', '$password')";
            $result = mysqli_query($dbconnect, $query);

            if ($result) {

            }
    }

    function isUsernameTaken ($username){

        $query = "SELECT username FROM user WHERE username = '$username'";
        $result = mysqli_query($dbconnect,$query);

        if ($result->num_rows > 0) {

            return true;

        }

        return false;
    }
