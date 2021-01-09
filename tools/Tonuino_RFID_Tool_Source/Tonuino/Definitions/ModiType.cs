
using System.Collections.Generic;

namespace Tonuino_RFID_Creator
{
    public enum EModiType
    {
        None,
        Sleep,
        StopDance,
        LockTonuino,
        Crawler,
        Kindergarden,
        TitleRepetition,
    }

    public class ModiType : BaseType<EModiType>
    {
        public ModiType(EModiType modiType) : base(modiType)
        {

        }

        protected override void createAllocation()
        {
            m_allocation = new List<Ident<EModiType>>
            {
                new Ident<EModiType>(0, EModiType.None, ""),
                new Ident<EModiType>(1, EModiType.Sleep, "Schlummer-Modus"),
                new Ident<EModiType>(2, EModiType.StopDance, "Stop-Tanz"),
                new Ident<EModiType>(3, EModiType.LockTonuino, "Tonuino sperren"),
                new Ident<EModiType>(4, EModiType.Crawler, "Krabbler-Modus"),
                new Ident<EModiType>(5, EModiType.Kindergarden, "Kindergarten-Modus"),
                new Ident<EModiType>(6, EModiType.TitleRepetition, "Titel wiederholen"),
            };
        }

        public bool UseSleepTimeSetting => Ident.Value == EModiType.Sleep;

        public static List<ModiType> AllValidModes()
        {
            List<EModiType> enumList = getEnumList();
            List<ModiType> retList = new List<ModiType>();
            foreach (EModiType mode in enumList)
            {
                if (mode != EModiType.None)
                {
                    retList.Add(new ModiType(mode));
                }
            }
            return retList;
        }
    }
}
