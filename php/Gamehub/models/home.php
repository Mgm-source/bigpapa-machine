<?php
require_once("../controllers/home.php");

function getLeaderBoard($dbconnect)
{

    $query = "SELECT name,username,duration,score FROM game INNER JOIN record ON game.id = record.game_id ORDER BY score DESC";
    $result = mysqli_query($dbconnect, $query);

    if ($result->num_rows > 0) {

        $data = array();

        while ($row = $result->fetch_assoc()) {
            $data[] = $row;
        }

        return $data;
    }

    return null;
}

function getRecord($username, $dbconnect)
{

    $query = "SELECT record.username, score FROM record INNER JOIN user ON record.username = record.username = '$username'";
    $result = mysqli_query($dbconnect, $query);

    if ($result->num_rows > 0) {

        

        $data = array();

        while ($row = $result->fetch_assoc()) {
            $data[] = $row;
        }

        return $data;
    }

    return null;
}
