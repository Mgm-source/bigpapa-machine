<?php

require_once 'header\header.php';
include_once 'misc\helper.php'; 
/* Using "include" to allow the script to allow to connect to the database and added "once" because 
you only need to connect once to the database in my case.
*/

if($Maintenance == true){

    echo "Site Unavailable";

}

getPages(); 
    
require_once 'footer\footer.php'; 
?>