using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    class GrenadeGun : Weapon, IFireable
    {
        private Grenade[] grenades;
        private int current;
        private const int max_grenades = 5;

        public GrenadeGun()
        {
            grenades = new Grenade[max_grenades];
            current = 0;
        }

        public override void info()
        {
            Console.WriteLine("Simpe granatome");
        }

        void IFireable.fire()
        {
            if (current < max_grenades)
            {
                (grenades[current] as ITimed).set_time(3);
                current++;
            }
        }
        bool IFireable.recharge()
        {
            grenades = new Grenade[max_grenades];
            current = 0;
            return true;
        }
    }
}
