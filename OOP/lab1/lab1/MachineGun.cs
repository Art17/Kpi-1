using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    class MachineGun : Weapon
    {
        private int speed;
        public MachineGun(int sp = 50) : base()
        {
            Console.Out.WriteLine("MachineGun constructor called");
            max_bullets = 50;
            sp = speed;
        }
        
        public override void info()
        {
            Console.Out.WriteLine("Simple machinegun");
        }
        public int Speed
        {
            get { return speed; }
            set
            {
                if (value >= 10 && value <= 100)
                    speed = value;
                else
                    speed = 50;
            }
        }
    }
}
