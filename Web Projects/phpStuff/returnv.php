<?php
include 'function.php';
?>

<?php

function sq($sqvalue){
	
	return $sqvalue * $sqvalue;
}
echo (sq(3));
?>
<br>

<?php
$degrees = 67;

if(check_temperature($degrees)){
	
	echo "Nice day";
}
else{ 

	echo "Not a nice day";
}

function check_temperature($tem){
	$return_v = false;
	if($tem > 65 && $tem < 75){
		
		$return_v = true;
	}
	return $return_v;
}
?>
<br>

<?php
$degree = 67;

if(check_temperatur($degree)){
	
	echo "Nice day";
}
else{ 

	echo "Not a nice day";
}

function check_temperatur($tem){
	
	if($tem > 65 && $tem < 75){
		
		return true;
	}
	return false;
}
?>