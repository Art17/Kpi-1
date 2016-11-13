using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    abstract class Weapon
    {
        protected int bullets = 8;
        protected int max_bullets = 8;

        public abstract void info();

        public virtual void fire()
        {
            Bullets--;
        }
        public virtual void recharge()
        {
            Bullets = max_bullets;
        }

        public virtual int Bullets
        {
            get { return bullets; }
            set
            {
                if (value > 0 && value < max_bullets)
                    bullets = value;
            }
        }
    }
}
