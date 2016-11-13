using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            MachineGun mg = new MachineGun(24);
            Gun g = new Gun();
            Riffle r = new Riffle(60);
            OpticalRiffle or = OpticalRiffle.createRiffle(40, 23.0);
            Weapon[] array = new Weapon[] { mg, g, r, or };

            g.Bullets = 3;
            Console.Out.WriteLine(g.Bullets);

            foreach (Weapon w in array) w.info();

            Console.In.Read();
        }
    }
}
