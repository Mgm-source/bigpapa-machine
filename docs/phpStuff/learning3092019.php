<html>
  <body>
  <H1>The math operation</H1>
   <?php 
   include 'function.php';
     echo "5+2=", 5+2,"<br>";
	 echo "5-2=", 5-2,"<br>";
	 echo "5*2=", 5*2,"<br>";
	 ?>
	 <H2>Assignment Operators</H2>
	 <?php
	 $a = $b = $c = 1;
	 echo ++$a.$b++.$c++.'<br>';
	 print($b);
	 
	?>
	<H3>Working with randoms</H3>
	<p>Whats the biggest between 2,22,0:</p>
	<?php
	echo(max(3,5,76,'z'));
	echo "<br>";
	echo(min(-123,1,0,122));
	echo "<br>";
	echo(mt_rand(10,mt_getrandmax()));
	?>
	<H4>Assignment Operators</H4>
	
	<p>Combine Operators</p>
	<?php
	$text = "No ";
	$total = 150;
	
	echo $text .="Worries.<br>";
	echo "Average = ", $total /3,"<br>";
	echo $text;
	
	$show = `dir c:\\temp`;
	echo $show; 
	echo "<br>";
	
	$temperature = 75; 
	
	if($temperature < 80)
	{
		echo "Fuck, its hot.";
	}
	?>
	
	 
	 </body>
	 </html>