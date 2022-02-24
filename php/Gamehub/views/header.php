<!DOCTYPE html>
<html lang="en">

<head>
   <meta charset="UTF-8">
   <meta name="viewport" content="width=device-width, initial-scale=1">
   <meta name="description" content="game scores">
   <!-- personal Stylesheet -->
   <link rel="stylesheet" href="css/style.css">
   <!-- personal JavaScript -->
   <script src="js/script.js"></script>
   <title><?php echo $title . " " . $tDesc; ?></title>
</head>

<body>
   <header >
      <a href='index.php'><img src="<?php echo $logo ?>" alt="<?php echo $slug ?>"></a>
      <?php if (!isset($_SESSION['loggedin'])) echo "<a href='?page=signin'>Sign in</a>"; ?>
      <?php if (!isset($_SESSION['loggedin'])) echo "<a href='?page=signup'>Sign up</a>"; ?>
      <?php if (isset($_SESSION['loggedin'])) echo  "<a href='models\signin.php'>Sign out</a>"; ?>
   </header>