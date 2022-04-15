<?php 
    require_once("controllers/account.php");

    function editAcount($username,$dbconnect){
        $query = "SELECT * password FROM user WHERE username = '$username'";

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
    
?>