<?php

require_once 'maintenance\config.php';

if (isset($_SESSION['username'])) {
   $username = $_SESSION['username'];
} else {
   $username = "Guest";
}

?>

<!DOCTYPE html>
<html lang="en">

<head>
   <meta charset="UTF-8">
   <meta name="viewport" content="width=device-width, initial-scale=1">
   <!-- Jquery -->
   <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
   <!-- Bootstrap with all its glory -->
   <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
   <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>
   <!-- Stylesheet -->
   <link rel="stylesheet" href="css/style.css">
   <title><?php echo $title . $tDash . $tDesc; ?></title>
</head>

<body>
   <header>
      <img src="<?php echo $logo ?>" alt="<?php echo $slug ?>">
      <h1>Hello, <?php echo $username ?></h1>
   </header>
   <nav>
      <ul>
         <li><a href='index.php'>GameHub</a></li>
         <li><a href='index.php?page=signin'>Sign-in</a></li>
         <li><a href='index.php?page=signup'>Sign-up</a></li>
         <li><a href='index.php?page=Account'>Account details</a></li>
         <li><a href='index.php?page=signout'>Sign-out</a></li>
         <li><a href='index.php?page=leaderboard'>Scores</a></li>
      </ul>
   </nav>