using System;

namespace lab
{
    class Test
    {


        static void valueTypes(){
            int intVar = 5; // 值类型 int, float ...
            Console.WriteLine(intVar);

            object objInt = intVar; // object类型 类似于oc中的id 值变量复制会发生box
            object sum = Convert.ToInt32(objInt) + 10;

            Console.WriteLine(sum);

            Console.WriteLine("sizeof int " + sizeof(int));
        }



        static void Main(string[] args) {
            valueTypes();
        }
    }
}

