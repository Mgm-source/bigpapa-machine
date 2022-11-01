<?php
    require_once("../controllers/signin.php");

    function signin($username,$password,$dbconnect){

        $query = "SELECT username, password FROM user WHERE username = '$username' AND password = '$password'";
        $result = mysqli_query($dbconnect, $query);
        
        if ($result->num_rows > 0) {

            $_SESSION['loggedin'] = true;
            $_SESSION['username'] = $username;

            return true;
            
        }

        return false;

    }

    function signout(){

        $_SESSION = array();

        setcookie(session_name(), "", time() - 2592000, '/');
        session_destroy();

    }
