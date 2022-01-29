<?php
session_start();
require_once 'maintenance\config.php';
require_once 'views\header.php';

if(!$maintenance){

    // solution need to route the pages
}else{

    echo "Site Unavailable";

}
    
require_once 'views\footer.php';
