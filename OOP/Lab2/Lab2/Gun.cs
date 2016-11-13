using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    class Gun : Weapon, IFireable
    {
        private int bullets;
        private const int max_bullets = 8;
        private DateTime noAmmoTime;

        public Gun()
        {
            bullets = max_bullets;
        }
        public override void info()
        {
            Console.WriteLine("Simpe gun");
        }
        void IFireable.fire()
        {
            if (bullets == 1)
            {
                noAmmoTime = DateTime.Now;
            }
            if (bullets > 0)
            {
                bullets--;
            }
            else
            {
                NoAmmoExceptionArgs args = new NoAmmoExceptionArgs(noAmmoTime);
                throw new NoAmmoException(args);
            }
        }
        bool IFireable.recharge()
        {
            this.bullets = max_bullets;
            return true;
        }

    }
}
