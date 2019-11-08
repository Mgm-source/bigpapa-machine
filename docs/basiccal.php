<?php
include 'function.php';
?>

<html>
<head>
	<meta charset = "UTF-8">
	<title>Basic Calculator</title>

<link href = "BasicC.css" rel ="stylesheet" type ="text/css"/>
</head>

<form action="basiccal.php" method="GET" class="Bascalcu">

<input type="number" name="num1">

<input list="operators" name="operator" id="operator">
<datalist id="operators">
<option value="*">
<option value="/">
<option value="+">
<option value="-">
<option value="%">
</datalist>



	</html>
 


<input type="number" name="num2">

<input type="submit" value="calculate">
</form>
<?php
$opr1=0;
$opr2=0;
$op="Please select an operator";

if(isset($_GET['num1']) && $_GET['num2'] && $_GET['operator'])
{
	$opr1 = $_GET['num1'];
	$opr2 = $_GET['num2'];
	$op = $_GET['operator'];
	
	switch($op){
		case "*":
		echo "$opr1 * $opr2 = ",$opr1*$opr2;
		break;
		case "/":
		echo "$opr1 / $opr2 = ",$opr1/$opr2;
		break;
		case "+":
		echo "$opr1 + $opr2 = ",$opr1+$opr2;
		break;
		case "-":
		echo "$opr1 - $opr2 = ",$opr1-$opr2;
		break;
		case "%":
		echo "$opr1 % $opr2 = ",$opr1%$opr2;
		break;
		default:
		echo "how did you break this";
		break;
	}
		
	}

else
{
	echo "Please enter values in to the calculator.<br>"; 
}


?>