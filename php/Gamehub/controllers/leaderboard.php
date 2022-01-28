<?php

if (isset($_SESSION['loggedin'])) {

    if (!$dbconnect) {

        die("Connection Failed: " . mysqli_connect_error());
        
    } else {

        $query = "SELECT * FROM game;";
        $result = mysqli_query($dbconnect, $query);

        if (mysqli_num_rows($result) > 0) {


        } else {

            
        }

        mysqli_close($dbconnect);
    }
}
