using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace Sudoku
{
    class Program
    {
        public static void DrawBoard(int[,] array)
        {
            var cutOff = new int[] { 2, 5 };
            Console.Write(String.Concat(Enumerable.Repeat("-", 45)) + "\n");
            for (int row = 0; row < array.Length / 9; row++)
            {
                for (int col = 0; col < array.Length / 9; col++)
                {
                    Console.Write(Slot(array[row, col]));
                }
                Console.Write("\n");
                if (Array.IndexOf(cutOff, row) != -1)
                {
                    Console.Write(String.Concat(Enumerable.Repeat("-", 45)) + "\n");
                }
            }
            Console.Write(String.Concat(Enumerable.Repeat("-", 45)) + "\n");
        }
        public static string Slot(int num)
        {
            return string.Format("| {0} |", num);
        }

        public static bool CheckValid(int[,] array, int row, int col, int num)
        {
            var startingRow = row - row % 3;
            var startingCol = col - col % 3;

            for (int i = 0; i < 9; i++)
            {
                if (array[row, i] == num)
                {
                    return false;
                }    
            }
            for (int i = 0; i < 9; i++)
            {
                if (array[i, col] == num)
                {
                    return false;
                }
            }
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (array[i + startingRow, j + startingCol] == num)
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        public static Tuple<int, int> FindEmpty(int[,] array)
        {
            for (int row = 0; row < 9; row++)
            {
                for (int col = 0; col < 9; col++)
                {
                    if (array[row, col] == 0)
                    {
                        return new Tuple<int, int>(row, col);
                    }
                }
            }
            return null;
        }
        public static bool Solver(int[,] array)
        {
            var replaceNum = new int[9] { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            var cord = FindEmpty(array);
            if (cord == null)
            {
                
                return true;
            }

            for (int i = 0; i < replaceNum.Length; i++)
            {
                
                if (CheckValid(array, cord.Item1, cord.Item2, replaceNum[i]))
                {
                    
                    array[cord.Item1, cord.Item2] = replaceNum[i];
                    if (Solver(array))
                    {
                        return true;
                    }
                    array[cord.Item1, cord.Item2] = 0;
                }
            }
            return false;
        }

        static void Main(string[] args)
        {
            var startTime = DateTime.Now.TimeOfDay;
            var boardArray = new int[9, 9] {
                 { 5,3,0, 0,7,0, 0,0,0 }
                ,{ 6,0,0, 1,9,5, 0,0,0 }
                ,{ 0,9,8, 0,0,0, 0,6,0 }

                ,{ 8,0,0, 0,6,0, 0,0,3 }
                ,{ 4,0,0, 8,0,3, 0,0,1 }
                ,{ 7,0,0, 0,2,0, 0,0,6 }

                ,{ 0,6,0, 0,0,0, 2,8,0 }
                ,{ 0,0,0, 4,1,9, 0,0,5 }
                ,{ 0,0,0, 0,8,0, 0,7,9 }};
            DrawBoard(boardArray);
            Solver(boardArray);
            Console.WriteLine("/////////////////////////////////////////////////////////////////////\n");
            DrawBoard(boardArray);
            Console.WriteLine("Solve Time -> {0}", DateTime.Now.TimeOfDay - startTime);
        }

    }
}
