<html>
<body>
<h1>Shitty If Statement</h1>
<?php
include 'function.php';
$Number = 9;

if($Number < 10)
{ 
for($i=0;$i<3;$i++)
{
echo "Its $Number"."TRUE";
echo "<br>";
}
}
elseif (round($Number) == 10)
{
echo "Its Equal";
}
else  
{
echo "Its $Number"."False";

}
echo "<br>";
echo $Number < 10 ? "Its $Number"."TRUE" : "Its $Number"."False";
?>
<h1>Shitty Case Statement</h1>
<?php
$temperature= 80;

switch($temperature)
{
case 70;
echo "hahaa easy weather";
break;

case 80;
echo "hahahaha im melting";
break;

default:
echo "below 70 or 90 Yikes";	
};
?>
<h1>For Loop</h1>
<?php
for($var1=2,$var2=2;$var1 <5 && $var2 <5;$var1++,$var2++)
{
echo "$var1 * $var2 = ".$var1*$var2,"<br>";
}
?>
<h1>While Loop</h1>
<?php
$value=1;
while(abs($value)<10)
{
echo "New value:", $value, "<br>";
$value--;
}
?>
<h1>Alternative IF Syntax </h1>
<?php
echo "<br>";
$value = 15;
if($value ==1):
echo "$value hold 1";
elseif ($value == 10):
echo "$value hold 10.";
else:
echo "$value does not hold 1 or 10";
endif;
?>
<h1>Alternative FOR syntax</h1>
<?php 
for ($loop_counter = 0; $loop_counter <5; $loop_counter++):
echo "I'm going to do this five times.<br>";
endfor;
?>
<h1>String functions </h1>
<?php
echo trim("   No worries."),"<br>";
echo substr("No worries.",3,1), "<br>";
echo "\"worries\" starts at position ", strpos("No  worries.","worries"), "<br>";
echo ucfirst("no worries."), "\n";
echo "\"No worries\" is ", strlen("No worries.")," characters"."<br>";
echo substr_replace("No worries  bro.","problems.",3,8);
$string = "hey";
$myfirstcharacter = $string{2};
echo $myfirstcharacter;

printf("i have %s apples and %s oranges.<br>",4,5);
?>
</body>
</html>