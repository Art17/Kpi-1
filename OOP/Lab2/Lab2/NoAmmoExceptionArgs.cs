using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    class NoAmmoExceptionArgs
    {
        DateTime time;
        public NoAmmoExceptionArgs (DateTime time)
        {
            this.time = time;
        }

        public DateTime Time
        {
            get { return time; }
        }
    }
}
