using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    class Grenade : Weapon, IExplodable, ITimed
    {
        bool is_valid = true;
        public override void info()
        {
            Console.WriteLine("Timed gronate");
        }

        bool IExplodable.explode()
        {
            if (is_valid)
            {
                is_valid = false;
                return true;
            }
            return false;
        }
        void ITimed.set_time(int secs)
        {
            System.Threading.Timer timer = null;
            timer = new System.Threading.Timer((obj) =>
            {
                ((IExplodable)this).explode();
                timer.Dispose();
            },
                        null, 1000*secs, System.Threading.Timeout.Infinite);
        }
    }
}
