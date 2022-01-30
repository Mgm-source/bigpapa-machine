<!DOCTYPE html>
<html lang="en">

<head>
   <meta charset="UTF-8">
   <meta name="viewport" content="width=device-width, initial-scale=1">
   <meta name="description" content="game scores">
   <!-- Bootstrap core CSS -->
   <link href="bootstrap/css/bootstrap.min.css" rel="stylesheet">
   <!-- Bootstrap core JavaScript -->
   <script src="bootstrap/js/bootstrap.bundle.min.js"></script>
   <!-- personal Stylesheet -->
   <link rel="stylesheet" href="css/style.css">
   <!-- personal JavaScript -->
   <script src="js/script.js"></script>
   <title><?php echo $title . " " . $tDesc; ?></title>
</head>

<body>
   <header class="navbar navbar-expand-lg navbar-light bg-light">
      <a class='navbar-brand' href='index.php'><img src="<?php echo $logo ?>" alt="<?php echo $slug ?>"></a>
      <?php if (!isset($_SESSION['loggedin'])) echo "<a class='nav-link' href='views\signin.php'>Sign in</a>"; ?>
      <?php if (!isset($_SESSION['loggedin'])) echo "<a class='nav-link' href='views\signup.php'>Sign up</a>"; ?>
      <?php if (isset($_SESSION['loggedin'])) echo  "<a class='nav-link' href='views\Account.php'>Account details</a>" ?>
      <?php if (isset($_SESSION['loggedin'])) echo  "<a class='nav-link' href='models\signin.php'>Sign out</a>"; ?>
   </header>
   <main class="container"></main>