using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    class OpticalRiffle : Riffle
    {
        private double precision;
        private static int count;
        static OpticalRiffle()
        {
            count = 0;
        }
        private OpticalRiffle(int l, double p) : base(l)
        {
            Console.Out.WriteLine("OpticalRiffle constructor called");
            count++;
            Precision = p;
        }

        public override void info()
        {
            Console.Out.WriteLine("Optical riffle");
        }
        public override void fire()
        {
            base.fire();
            precision-=0.001;
        }
        public double Precision
        {
            get { return precision; }
            set
            {
                if (value >= 20 && value <= 100)
                    precision = value;
                else
                    precision = 50;
            }
        }
        public static OpticalRiffle createRiffle(int l, double p)
        {
            if (count < 10)
                return new OpticalRiffle(l, p);
            else
                return null;
        }

    }
}
