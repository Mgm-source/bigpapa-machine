<?php

require_once("../maintenance/config.php");

    if (!$dbconnect) {

        die("500 Internal Server Error " . mysqli_connect_error());
    }

    if(count($_GET) == 2 && $_GET['page']=='record' && $_GET['user']){
        header('Content-Type: application/json; charset=utf-8');
        echo json_encode(getRecord($username,$dbconnect));

	}

	if(count($_GET) == 1 && $_GET['page']=='leaderboard'){
        header('Content-Type: application/json; charset=utf-8');
        echo json_encode(getLeaderBoard($dbconnect));
	}
