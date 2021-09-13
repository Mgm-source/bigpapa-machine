<?php
require_once '../misc/helper.php'; 

/*The function test script don't think need more explaining*/

$test = "dadada";
$test2 = "1";
$test3 = "1da";

echo ("<div id=\"output\">this element will be accessed by jquery and this text replaced</div>");

if(Charspace($test,$test2,$test3))
{
  echo "Success";
}
else
{
 echo "failure";
}

echo"<br>";

echo(encrptpass("dada"));
phpversion();