<?php
require_once 'maintenance\config.php';
include_once 'misc\helper.php'; 
require_once 'views\header.php';
/* Using "include" to allow the script to allow to connect to the database and added "once" because 
you only need to connect once to the database in my case.
*/

if($maintenance){

    echo "Site Unavailable";

}else{

    getPages(); 

}
    
require_once 'views\footer.php'; 
?>