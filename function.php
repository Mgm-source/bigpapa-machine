
<?php
function navbar()
{
	echo "<hr>";
	echo "<center>";
	echo "<a href='basiccal.php'>Calculator</a>&nbsp;&nbsp;&nbsp;";
	echo "<a href='useinput.php'>Register</a>&nbsp;&nbsp;&nbsp;";
	echo "<a href='learning3092019.php'>Operators</a>&nbsp;&nbsp;&nbsp;";
	echo "<a href='Learning08102019.php'>If Statement</a>&nbsp;&nbsp;&nbsp;";
	echo "<a href='Learning18102019.php'>Arrays</a>&nbsp;&nbsp;&nbsp;";
	echo "</center>";
	
}

function navbar2($text,$copyright)
{
	echo "<hr>";
	echo "<center>";
	echo "<a href='returnv.php'>Functions</a>&nbsp;&nbsp;&nbsp;";
	echo "<a href='basiccal.php'>Calculator</a>&nbsp;&nbsp;&nbsp;";
	echo "<a href='useinput.php'>Register</a>&nbsp;&nbsp;&nbsp;";
	echo "<a href='learning3092019.php'>Operators</a>&nbsp;&nbsp;&nbsp;";
	echo "<a href='Learning08102019.php'>If Statement</a>&nbsp;&nbsp;&nbsp;";
	echo "<a href='Learning18102019.php'>Arrays</a>&nbsp;&nbsp;&nbsp;";
	echo "<hr>";
	echo "<Font Size='1'><I>$text</I></Font>";
	echo "<br><Font Size='1'><I>$copyright</I></Font>";
	echo "</center>";
	
}
 navbar2("MGM Co","(C) 2019");
 ?> 
