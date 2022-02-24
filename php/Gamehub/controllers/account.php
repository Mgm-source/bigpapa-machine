<?php
if (isset($_SESSION['loggedin'])) {

   $_SESSION['edit']  = editAcount($_SESSION['username'], $dbconnect);
	
}
