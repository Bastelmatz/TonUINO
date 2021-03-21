
using System.Collections.Generic;

namespace Tonuino_RFID_Creator
{
    public enum ELegacyModiType
    {
        None,
        Sleep,
        StopDance,
        LockTonuino,
        Crawler,
        Kindergarden,
        TitleRepetition,
    }

    public class LegacyModiType : BaseType<ELegacyModiType>
    {
        public LegacyModiType(ELegacyModiType modiType) : base(modiType)
        {

        }

        protected override void createAllocation()
        {
            m_allocation = new List<Ident<ELegacyModiType>>
            {
                new Ident<ELegacyModiType>(0, ELegacyModiType.None, ""),
                new Ident<ELegacyModiType>(1, ELegacyModiType.Sleep, "Schlummer-Modus"),
                new Ident<ELegacyModiType>(2, ELegacyModiType.StopDance, "Stop-Tanz"),
                new Ident<ELegacyModiType>(3, ELegacyModiType.LockTonuino, "Tonuino sperren"),
                new Ident<ELegacyModiType>(4, ELegacyModiType.Crawler, "Krabbler-Modus"),
                new Ident<ELegacyModiType>(5, ELegacyModiType.Kindergarden, "Kindergarten-Modus"),
                new Ident<ELegacyModiType>(6, ELegacyModiType.TitleRepetition, "Titel wiederholen"),
            };
        }

        public bool UseSleepTimeSetting => Ident.Value == ELegacyModiType.Sleep;

        public static List<LegacyModiType> AllValidModes()
        {
            List<ELegacyModiType> enumList = getEnumList();
            List<LegacyModiType> retList = new List<LegacyModiType>();
            foreach (ELegacyModiType mode in enumList)
            {
                if (mode != ELegacyModiType.None)
                {
                    retList.Add(new LegacyModiType(mode));
                }
            }
            return retList;
        }
    }
}
