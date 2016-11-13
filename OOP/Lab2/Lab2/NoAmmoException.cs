using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    class NoAmmoException : Exception
    {
        NoAmmoExceptionArgs args;
        public NoAmmoException()
        {
            this.args = new NoAmmoExceptionArgs(DateTime.Now);
        }

        public NoAmmoException(NoAmmoExceptionArgs args)
        {
            this.args = args;
        }

        public NoAmmoExceptionArgs Args
        {
            get { return args; }
        }
    }
}
