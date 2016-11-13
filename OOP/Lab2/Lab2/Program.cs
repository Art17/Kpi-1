using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    class Program
    {
        static void Main(string[] args)
        {
            Shop mainShop = new Shop();
            Policeman Alex = new Policeman(1);
            Policeman John = new Policeman(2);
            Policeman Rick = new Policeman(3);

            Alex.subscribe_on_shop_weapon_bought(mainShop);
            John.subscribe_on_shop_weapon_bought(mainShop);

            Gun my_gun = mainShop.get_gun("Darrel");

            for (int i = 0; i < 16; i++)
            {
                try
                {
                    ((IFireable)my_gun).fire();
                }
                catch(NoAmmoException e)
                {
                    Console.WriteLine("NoAmmoException exception caught");
                    Console.WriteLine(String.Format("Bullets ended on " + e.Args.Time.ToString()));
                    ((IFireable)my_gun).recharge();
                }

            }

            Console.In.Read();
        }
    }
}
