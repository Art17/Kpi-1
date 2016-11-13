using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    class Policeman
    {
        private int badge;

        public Policeman(int badge)
        {
            this.badge = badge;
        }

        public void subscribe_on_shop_weapon_bought(Shop shop)
        {
            shop.WeaponBought += new WeaponBoughtEventHandler(Shop_WeaponBought);
        }

        private void Shop_WeaponBought(object s, WeaponBoughtEventArgs args)
        {
            Console.WriteLine(String.Format("Policeman with badge {0} received that {1} bought weapon", badge, args.Name));
        }
    }
}
