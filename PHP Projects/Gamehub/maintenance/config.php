<?php

/* Starts a new or resumes an existing session.
This needed so that all the session data will be available
 */

session_start();

// Login for the database
$dbhost  = 'localhost';
$dbuser  = 'root';
$dbpass  = '';
$dbname  = 'gamehub';

/* Redirect to a different page in the current directory that was requested */
$home = "http://localhost/Uni-work/Gamehub";


//Creation of connection
$dbconnect = mysqli_connect($dbhost,$dbuser,$dbpass,$dbname) or die(mysqli_connect_error());


//Checking connection
    if(!$dbconnect)
    {

        die("Connection Failed: " . mysqli_connect_error());

    }   

        $query = "SELECT * FROM conf";
        $result = mysqli_query($dbconnect, $query);
        $row = mysqli_fetch_assoc($result);

        // General settings 
        $title = $row['conf_title'];
        $tDash = $row['conf_dash'];
        $tDesc = $row['conf_desc'];
        $slug =  $row['conf_slug'];
        $logo =  $row['conf_image'];

        // Techincial Settings
        $Maintenance = $row['conf_maintenance'];
?>
      