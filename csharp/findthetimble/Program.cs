class Game
{
    private int x, y;

    private int Guess = 1;

    private static readonly string thimble = " "; //"thimble"

    private static readonly string thimble2 = "t";

    private string[,] gameroom = new string[10, 10];

    private int randomthimbleX;

    private int randomthimbleY;

    public void Thegame()
    {

        while (Yn())
        {
            Rando();

            Declare();

            HiddenTimble();

            do
            {
                UserCoordinates();

                Distance();

                Display();

            } while (gameroom[x, y] != HiddenTimble());

        }

        Console.WriteLine("Press any key to quit..");

        Console.ReadKey();

    }

    public string HiddenTimble()
    {
        // hides "thimble" in the array
        // probs should implement this without the assigmnet to the array happening every time
        // normal game
        //gameroom[randomthimbleX, randomthimbleY] = thimble;
        // cheat 
        return gameroom[randomthimbleX, randomthimbleY] = thimble2;

    }

    public void Declare()
    {

        // Declaring the array

        for (int i = 0; i < gameroom.GetLength(0); i++)
        {

            for (int j = 0; j < gameroom.GetLength(1); j++)
            {

                gameroom[j, i] = "#";

            }

        }

    }

    public void UserCoordinates()
    {

        // Enter guess

        Console.WriteLine("\nNew Guess");

        Console.Write("Enter the X-coordinate: ");

        x = Convert.ToInt32(Console.ReadLine());

        Console.Write("Enter the Y-coordinate: ");

        y = Convert.ToInt32(Console.ReadLine());

        if (gameroom[x, y] != HiddenTimble())
        {

            gameroom[x, y] = "*";
            Guess++;
        }
    }

    public void Rando()
    {

        // random number generator

        Random rnd = new();

        randomthimbleX = rnd.Next(9);

        randomthimbleY = rnd.Next(9);

    }

    public void Distance()
    {

        // win condition

        if (gameroom[x, y] == HiddenTimble())
        {

            Console.WriteLine("\nCongratulations you found the Thimble!");

            Console.WriteLine("\nYou managed to find the Thimble in " + Guess + " guess(es).");

        }

        // distance feedback

        else if ((Math.Abs(randomthimbleY - y) >= 7) || (Math.Abs(randomthimbleX - x) >= 7))
        {

            Console.WriteLine("\nFreezing");

        }

        else if ((Math.Abs(randomthimbleY - y) >= 5) || (Math.Abs(randomthimbleX - x) >= 5))
        {

            Console.WriteLine("\ncold");

        }

        else if ((Math.Abs(randomthimbleY - y) >= 3) || (Math.Abs(randomthimbleX - x) >= 3))
        {

            Console.WriteLine("\nwarm");

        }

        else if ((Math.Abs(randomthimbleY - y) >= 1) || (Math.Abs(randomthimbleX - x) >= 1))
        {

            Console.WriteLine("\nhot");

        }

    }

    static public bool Yn()
    {

        Console.WriteLine("Do you want to play Find The Thimble? Y/ANY OTHER CHARACTER");

        string Yesno = Console.ReadLine()!.ToLower();

        Console.Clear();

        return Yesno == "y";

    }

    public void Display()
    {

        // show grid

        Console.WriteLine("play| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |");

        for (int i = 0; i < gameroom.GetLength(0); i++)
        {
            Console.WriteLine("---------------------------------------------");
            Console.Write("| " + i);

            for (int j = 0; j < gameroom.GetLength(1); j++)
            {

                Console.Write(" | ");

                Console.Write(gameroom[j, i]);

            }

            Console.WriteLine(" |");

        }

    }

    static void Main()
    {
        Game game = new();

        game.Thegame();


    }
}