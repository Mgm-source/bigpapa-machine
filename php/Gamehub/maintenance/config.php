<?php
session_start();
/* Starts a new or resumes an existing session.
This needed so that all the session data will be available
 */

// Login for the database
$dbhost  = 'localhost';
$dbuser  = 'root';
$dbpass  = 'shemuna2008';
$dbname  = 'gamehub';

/* Redirect to a different page in the current directory that was requested */
$home = "http://localhost/bigpapa-machine/php/Gamehub";


//Creation of connection
$dbconnect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die(mysqli_connect_error());


$query = "SELECT * FROM conf where id=( select max(id) from conf)";
$result = mysqli_query($dbconnect, $query);

$row = null;

if (mysqli_num_rows($result)) {

    $row = mysqli_fetch_assoc($result);

    // General settings 
    $title = $row['title'];
    $tDesc = $row['description'];
    $slug =  $row['slug'];
    $logo =  $row['image'];

    // Techincial Settings
    $maintenance = $row['maintenance'];
}

if ($row === null) {
    // create error page
    $maintenance = true;
    $title = "GameHub";
    $tDesc = "Currently Down";
    $slug =  "Site-offline";
    $logo = "assets\gamehub_logo_f.png";
}

// Checks if the password is the same 
function verifyPass($password, $password2)
{
    if ($password === $password2) {
        return true;
    }
    return false;
}

// removes any unwanted string to be sent to the database
function validinput($vinput, $conn, $charM = " \t\n\r\0\x0B")
{
    // trim() removes the whitespaces from the beginning and the end of the 'string' parameter 
    $vinput = trim($vinput, $charM);
    $vinput = stripslashes($vinput);
    $vinput = htmlspecialchars($vinput);
    $vinput = mysqli_real_escape_string($conn, $vinput);
    return $vinput;
}

function encrptpass($password)
{
    $password = md5($password);

    return $password;
}

function redirect($page)
{
    $host  = $_SERVER['HTTP_HOST'];
    $uri   = "/bigpapa-machine/php/Gamehub/index.php";
    if($page == "home"){
        header("Location: http://$host$uri");
    }else{
        header("Location: http://$host$uri?page=$page");
    }  
    die();
}


function getBody()
{
    if (isset($_GET['page'])) {

        $page = "views/" . $_GET['page'] . ".php";

        if (file_exists($page) ) {

            echo file_get_contents($page);

        }else{
            echo "<span>Page doesn't exist!</span>";
        }
    }
}
