<?php
require_once("../controllers/home.php");

function getLeaderBoard($dbconnect)
{

    $query = "SELECT name,username,duration,score FROM game join record ON game.id = record.game_id";
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

    $query = "SELECT * FROM record join user ON record.username = users.username WHERE user.username = '$username'";
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
