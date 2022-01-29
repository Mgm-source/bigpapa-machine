<?php 
    require_once("../controllers/account.php");

    function getRecord($username){
        
        $query = "SELECT * FROM record left join user ON record.username = users.username WHERE user.username = '$username'";
		$result = mysqli_query($dbconnect, $query);
	
		if ($result->num_rows > 0) {
	
			return $result->fetch_assoc();
		}

        return null;
    }
    
    function getLeaderBoard(){

        $query = "SELECT * FROM game";
		$result = mysqli_query($dbconnect, $query);
	
		if ($result->num_rows > 0) {
			return $result->fetch_assoc();
		}

        return null;

    }
?>