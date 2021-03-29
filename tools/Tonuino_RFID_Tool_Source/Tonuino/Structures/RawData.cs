
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace Tonuino_RFID_Tool
{
    public static class RawData
    {
        static RawData()
        {
            m_listBytes.Clear();
            for (int i = 0; i < CardData.MAXBYTES; i++)
            {
                m_listBytes.Add(0);
            }

            // set Tonuino default
            for (int i = 0; i < CardData.FirstTonuinoBytes.Count; i++)
            {
                SetByte(i, CardData.FirstTonuinoBytes[i]);
            }
        }

        private static List<byte> m_listBytes = new List<byte>();
        public static ReadOnlyCollection<byte> ListBytes => m_listBytes.AsReadOnly();

        public static void SetByte(int index, byte value)
        {
            if (index < ListBytes.Count)
            {
                m_listBytes[index] = value;
            }
        }
    }

}
