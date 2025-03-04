using System;

namespace Test {
   namespace Nested1 {
      class Program {
         static void Main(string[] args) { }
      }
    }
   
   namespace Nested2 {
      class test {

      }
   }
}

namespace Test2.Dot1 {
   class Test { }
}

namespace Test2.Dot2 {
   class Test { }
}

namespace Test2.Dot2 {
   class Test2 { }
}

class test {
   Test.Nested2.test objTest;
   Test2.Dot1.Test objTest2;
   Test2.Dot2.Test objTest3;
   Test2.Dot2.Test2 objTest4;
}