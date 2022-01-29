<?php

/* Starts a new or resumes an existing session.
This needed so that all the session data will be available
 */

// Login for the database
$dbhost  = 'localhost';
$dbuser  = 'root';
$dbpass  = 'admin';
$dbname  = 'gamehub';

/* Redirect to a different page in the current directory that was requested */
$home = "http://localhost/bigpapa-machine/php/Gamehub";


//Creation of connection
$dbconnect = mysqli_connect($dbhost,$dbuser,$dbpass,$dbname) or die(mysqli_connect_error());


        $query = "SELECT * FROM conf where id=( select max(id) from conf)";
        $result = mysqli_query($dbconnect, $query);

        $row = "failed";

        if( mysqli_num_rows($result))
        {

        $row = mysqli_fetch_assoc($result);

        // General settings 
        $title = $row['title'];
        $tDesc = $row['description'];
        $slug =  $row['slug'];
        $logo =  $row['image'];

        // Techincial Settings
        $maintenance = $row['maintenance'];

        }

        if($row == "failed"){
            // create error page
            $maintenance = true;
            $title = "GameHub";
            $tDesc = "Currently Down";
            $slug =  "Site-offline";
            $logo = "assets\gamehub_logo_f.png";
        }
