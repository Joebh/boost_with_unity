using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.networking
{
    class SendingStructure
    {
        public byte[] data;
        public int hash;

        public SendingStructure(byte[] data, int hash)
        {
            this.data = data;
            this.hash = hash;
        }
        
    }
}
