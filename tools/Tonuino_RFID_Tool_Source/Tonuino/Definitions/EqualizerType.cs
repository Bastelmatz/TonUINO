
using System.Collections.Generic;

namespace Tonuino_RFID_Tool
{
    public enum EEqualizerType
    {
        Normal,
        Pop,
        Rock,
        Jazz,
        Klassik,
        Bass,
    }

    public class EqualizerType : BaseType<EEqualizerType>
    {
        public EqualizerType(EEqualizerType equalizer) : base(equalizer)
        {

        }

        protected override void createAllocation()
        {
            // Attention:
            // Value that is send/valid to DFPlayer is <Index - 1>
            // This decrement is done by Tonuino software
            m_allocation = new List<Ident<EEqualizerType>>
            {
                new Ident<EEqualizerType>(1, EEqualizerType.Normal, "Normal"),
                new Ident<EEqualizerType>(2, EEqualizerType.Pop, "Pop"),
                new Ident<EEqualizerType>(3, EEqualizerType.Rock, "Rock"),
                new Ident<EEqualizerType>(4, EEqualizerType.Jazz, "Jazz"),
                new Ident<EEqualizerType>(5, EEqualizerType.Klassik, "Klassik"),
                new Ident<EEqualizerType>(6, EEqualizerType.Bass, "Bass"),
            };
        }

        public static List<EqualizerType> AllValidModes()
        {
            List<EEqualizerType> enumList = getEnumList();
            List<EqualizerType> retList = new List<EqualizerType>();
            foreach (EEqualizerType mode in enumList)
            {
                retList.Add(new EqualizerType(mode));
            }
            return retList;
        }
    }
}
