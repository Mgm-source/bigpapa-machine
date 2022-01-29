 <?php

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
        $uri   = rtrim(dirname($_SERVER['PHP_SELF']), '/\\');
        header("Location: http://$host$uri/$page");
        die();
    }
