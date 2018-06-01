using System;
using System.Collections.Generic;

class MainClass
{
    static void Main()
    {
        /*
		Machine initialization...
		*/

        string Input;
        Console.WriteLine("Enter X to exit.");
        while (true)
        {
            Console.Write("Enter transition string: ");
            Input = Console.ReadLine();
            if (Input.CompareTo("X") == 0)
                break;
            Console.WriteLine(DFA.Transition(Input));
        }
    }
}
