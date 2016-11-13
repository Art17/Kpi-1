using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    public delegate void WeaponBoughtEventHandler(object sender, WeaponBoughtEventArgs args);

    class Shop
    {
        public event WeaponBoughtEventHandler WeaponBought;

        public Gun get_gun(string name)
        {
            WeaponBoughtEventArgs args = new WeaponBoughtEventArgs(name);
            onWeaponBought(args);
            return new Gun();
        }
        protected virtual void onWeaponBought(WeaponBoughtEventArgs args)
        {
            WeaponBought(this, args);
        }

    }
}
