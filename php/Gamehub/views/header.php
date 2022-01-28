<!DOCTYPE html>
<html lang="en">
<head>
   <meta charset="UTF-8">
   <meta name="viewport" content="width=device-width, initial-scale=1">
   <!-- Jquery -->
   <script src="https://code.jquery.com/jquery-3.6.0.min.js" integrity="sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4=" crossorigin="anonymous"></script>
   <!-- Bootstrap with all its glory -->
   <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>
   <!-- Stylesheet -->
   <link rel="stylesheet" href="css/style.css">
   <title><?php echo $title ." ". $tDesc; ?></title>
</head>
<body>
   <header>
      <img src="<?php echo $logo ?>" alt="<?php echo $slug ?>">
   </header>
   <nav>
      <ul>
         <li><a href=''>GameHub</a></li>
         <li><a href='?page=signin'>Sign-in</a></li>
         <li><a href='?page=signup'>Sign-up</a></li>
         <li><a href='?page=Account'>Account details</a></li>
         <li><a href='?page=signout'>Sign-out</a></li>
         <li><a href='?page=leaderboard'>Scores</a></li>
      </ul>
   </nav>