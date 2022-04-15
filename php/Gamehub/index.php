<?php
include 'maintenance\config.php';
require_once 'views\header.php';

if(!$maintenance){

    getBody();
    
}else{

    echo "Site Unavailable";

}
    
require_once 'views\footer.php';
