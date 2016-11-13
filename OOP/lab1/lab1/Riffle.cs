using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    class Riffle : Weapon
    {
        private int length;

        public Riffle (int len) : base()
        {
            Console.Out.WriteLine("Riffle constructor called");
            Length = len;
        }

        public override void info()
        {
            Console.Out.WriteLine("Simple Riffle");
        }
        public int Length
        {
            get { return length; }
            set
            {
                if (value > 0 && value < 200)
                    length = value;
                else
                    length = 100;
            }
        }

    }
}
