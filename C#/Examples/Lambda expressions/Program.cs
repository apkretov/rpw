using System;

namespace ConsoleApplication1 {
   class Program {
      private delegate int TestDelegate(int a, int b);
      private static int Add(int a, int b) { return a + b; }
      private static int Subtract(int a, int b) { return a - b; }

      static void Main(string[] args) {
         TestDelegate ptrAdd = Add;
         Console.WriteLine("{0}", ptrAdd(10, 20));
         TestDelegate ptrSubstractExplicit = (int a, int b) => (a - b);
         Console.WriteLine("{0}", ptrSubstractExplicit(50, 30));
         TestDelegate ptrSubstractImplicit = (a, b) => (a - b);
         Console.WriteLine("{0}", ptrSubstractImplicit(200, 50));
      }
   }
}
