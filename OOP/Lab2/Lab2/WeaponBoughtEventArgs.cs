using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    public class WeaponBoughtEventArgs : EventArgs
    {
        private string name;
        public WeaponBoughtEventArgs (string name)
        {
            this.name = name;
        }

        public string Name
        {
            get { return name; }
        }

    }
}
