<?php

if(!isset($_SESSION['loggedin']))
{

    echo "You must be logged in to sign-out.<br>";
    header("refresh:5; url=index.php?msg=logoutSuccess");

}
else
{
    $_SESSION = array();

    setcookie(session_name(), "", time() - 2592000, '/');
    session_destroy();

    echo "You have logged out";
    header("refresh:2; url=index.php?msg=logoutSuccess");
    
}