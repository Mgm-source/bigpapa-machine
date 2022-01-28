<?php

if (isset($_SESSION['loggedin'])) {

    if (!$dbconnect) {

        die("Connection Failed: " . mysqli_connect_error());
        
    } else {

        $query = "SELECT * FROM players;";
        $result = mysqli_query($dbconnect, $query);

        if (mysqli_num_rows($result) > 0) {

            while ($row = mysqli_fetch_assoc($result)) {

                printf("Nickname: %s Score: %s",  $row["player_nickname"], $row["player_score"]);
            }
        } else {

            echo ("Leaderboard empty");
        }

        mysqli_close($dbconnect);
    }
}
