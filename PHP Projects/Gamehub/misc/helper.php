 <?php

    function getPages()
    {
        $page = '';

        if (isset($_GET['page'])) {
            $page = $_GET['page'];

            if ($page == 'index') {
                require_once 'index.php';
            } elseif ($page == 'signin') {
                require_once 'registration\signin.php';
            } elseif ($page == 'signup') {
                require_once 'registration\signup.php';
            } elseif ($page == 'Account') {
                require_once 'view\account.php';
            } elseif ($page == 'signout') {
                require_once 'registration\signout.php';
            } elseif ($page == 'leaderboard') {
                require_once 'view\leaderboard.php';
            }
        } else {
            require_once 'index.php';
        }
    }
    // Checks if the password is the same 
    function verifyPass($password, $password2)
    {
        if ($password === $password2) {
            return true;
        }
        return false;
    }
    // checks if the password field is empty 
    function emptyPass($password)
    {
        if (empty($password)) {
            return true;
        }
        return false;
    }

    // validates if there is empty spaces on the 'string' parameter

    function Charspace()
    {
        $textargs = func_get_args();
        $scompare = chr(32);

        for ($i = 0; $i < func_num_args(); $i++) {

            if($textargs[$i] == ""){
                return true;
            }

            for ($j = 0; $j < strlen($textargs[$i]); $j++) {

                if ($scompare[0] === $textargs[$i][$j]) {
                    return true;
                }

            }
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
    function refreshpage()
    {
        header('location:index.php');
    }

    function encrptpass($password)
    {
        $password = md5($password);

        return $password;
    }
