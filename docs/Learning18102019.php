<?php
include 'function.php';
$float = 4.233423;

echo (string) $float,"<br>";
echo strval($float),"<br>";

?>
<br>
<?php
$float = " -4"+-5;

echo (string) $float,"<br>";
echo strval($float),"<br>";

?>
<br>
<?php
$number = 1+"14.5";
echo "$number<br>";
$number = 1 + "-1.5e2";
echo "$number<br>";
$text = "5.0";
$number = (float) $text;
echo $number / 2.0, "<br>";

?>
<br>
<?php
$fruits[0] = "Pineapple";
$value = range("a","z"); 
$fruits[1] = "Watermelon";
$fruits[]= "Apples";
unset($fruits[4]);
print_r($fruits);
for($i=0;$i < count($fruits);$i++)
{
echo  $fruits[$i],"<br>";
}
?>
<br>
<?php
$apple_inventory["Pittsburgh"]= 2343;
$apple_inventory["Albany"]= 5773;
$apple_inventory["Houston"]= 1884;

echo $apple_inventory["Pittsburgh"];
?>

<?php


$testscore["Frank"][1] = "intellect";
$testscore["Mary"][2] = "genius";
$testscore["Mary"][1]= "Simply bad";
$testscore["Benny"][1] = "Smart";
$testscore["Benny"][2] = "N/A";
$testscore["Frank"][2] = "Idiot";


print_r($testscore);

echo "<br>";

foreach($testscore as $outer_key => $array_single)
{
	foreach($array_single as $inner_key => $value)
	{
	echo "\$testscore[$outer_key][$inner_key] = $value";
}
}
echo "<br>";
$apple_inventor[0]= 2343;
$apple_inventor[1]= 5773;
$apple_inventor[2]= 1884;

function arrayecho($array)
{
	for($i=0;$i<count($array);$i++){
		echo "Element $i: ", $array[$i],"<br>";
	}
}

function arrayAverecho($array)
{
	$total = 0;
	for($i=0;$i<count($array);$i++){
		$total += $array[$i];
	}
	echo "Average score = ",$total/count($array);
}

 arrayecho($apple_inventor);
 
 arrayAverecho($apple_inventor);





?>