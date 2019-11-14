// using System;

namespace FindTheThimble

{

    class Game

    {

        static int x, y;

        static int Guess = 1;

        static string thimble = "t"; //"thimble"

        static string[,] gameroom = new string[10, 10];

        static string Yesno;

        static int randomthimbleX;

        static int randomthimbleY;

        static void Thegame()

        {

            do

            {

                Yn();

                if (Yesno == "Y" || Yesno == "y")

                {

                    rando();

                    do

                    {

                        Declare();

                        HideTimble();

                        UserCoordinates();

                        display();

                        distance();

                    } while (gameroom[x, y] != thimble);

                }

            } while (Yesno != "n" && Yesno != "N");

            System.Console.WriteLine("Press any key to continue..");

            System.Console.ReadKey();

        }

        static void HideTimble()

        {

            // hides "thimble" in the array

            gameroom[randomthimbleX, randomthimbleY] = thimble;

        }

        static void Declare()

        {

            // Declaring the array

            for (int i = 0; i < gameroom.GetLength(0); i++)

            {

                for (int j = 0; j < gameroom.GetLength(1); j++)

                {

                    gameroom[j, i] = " ";

                }

            }

        }

        static void UserCoordinates()

        {

            // Enter guess

            System.Console.WriteLine("\nNew Guess");

            System.Console.Write("Enter the X-coordinate: ");

            x = System.Convert.ToInt32(System.Console.ReadLine());

            System.Console.Write("Enter the Y-coordinate: ");

            y = System.Convert.ToInt32(System.Console.ReadLine());

            if (gameroom[x, y] != thimble)

            {

                gameroom[x, y] = "*";

            }
            Guess++;
        }

        static void rando()

        {

            // random number generator

            System.Random rnd = new System.Random();

            randomthimbleX = rnd.Next(9);

            randomthimbleY = rnd.Next(9);

        }

        static void distance()

        {

            // win condition

            if (gameroom[x, y] == gameroom[randomthimbleX, randomthimbleY])

            {

                System.Console.WriteLine("\nCongratulations you found the Thimble!");

                System.Console.WriteLine("\nYou managed to find the Thimble in " + Guess + " guess(es).");

                Guess++;

            }

            // distance feedback

            else if ((System.Math.Abs(randomthimbleY - y) >= 7) || (System.Math.Abs(randomthimbleX - x) >= 7))

            {

                System.Console.WriteLine("Freezing");

            }

            else if ((System.Math.Abs(randomthimbleY - y) >= 5) || (System.Math.Abs(randomthimbleX - x) >= 5))

            {

                System.Console.WriteLine("cold");

            }

            else if ((System.Math.Abs(randomthimbleY - y) >= 3) || (System.Math.Abs(randomthimbleX - x) >= 3))

            {

                System.Console.WriteLine("warm");

            }

            else if ((System.Math.Abs(randomthimbleY - y) >= 1) || (System.Math.Abs(randomthimbleX - x) >= 1))

            {

                System.Console.WriteLine("hot");

            }

        }

        static void Yn()

        {

            System.Console.WriteLine("Do you want to play Find The Thimble? Y/N");

            Yesno = System.Console.ReadLine();

            System.Console.Clear();

        }

        static void display()

        {

            // show grid

            System.Console.WriteLine("  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |");

            for (int i = 0; i < gameroom.GetLength(0); i++)

            {

                System.Console.Write(i);

                for (int j = 0; j < gameroom.GetLength(1); j++)

                {

                    System.Console.Write(" | ");

                    System.Console.Write(gameroom[j, i]);

                }

                System.Console.WriteLine("|");

                System.Console.WriteLine("----------------------------------------------------------------------------------------------");

            }

        }

        static void Main(string[] args)

        {

            Thegame();

        }

    }

}