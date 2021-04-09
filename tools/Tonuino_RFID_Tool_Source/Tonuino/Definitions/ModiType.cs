
using System.Collections.Generic;

namespace Tonuino_RFID_Tool
{
    public enum EModiType
    {
        None,
        TrackContinue,
        TrackNext,
        TrackPrevious,
        TrackFirst,
        TrackLast,
        TrackNumber,

        ShortCut,
        Advertisement,

        Player_StandbyTime,
        Player_SleepTime,
        Player_Volume,
        Player_VolumeUp,
        Player_VolumeDown,

        Player_Random,
        Player_RepeatSingle,
        Player_RepeatAll,
        Player_ListenToEnd,
        Player_StopOnCardRemoval,

        Player_FreezeDance,
        Player_MemoryMode,
        Player_RandomQuiz,

        LockAll,
        LockButtons,

        SetupCard,
        ResetCard,
        ResetEEPROM,

        MENU_ChangeSmall,
        MENU_ChangeLarge,
        MENU_Choose,
        MENU_Cancel,
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
                new Ident<EModiType>(1, EModiType.TrackContinue, "Track Continue"),
                new Ident<EModiType>(2, EModiType.TrackNext, "Track Next"),
                new Ident<EModiType>(3, EModiType.TrackPrevious, "Track Previous"),
                new Ident<EModiType>(4, EModiType.TrackFirst, "Track First"),
                new Ident<EModiType>(5, EModiType.TrackLast, "Track Last"),
                new Ident<EModiType>(6, EModiType.TrackNumber, "Play Current Tracknumber"),

                new Ident<EModiType>(10, EModiType.ShortCut, "Play Shortcut"),
                new Ident<EModiType>(11, EModiType.Advertisement, "Play Advertisement"),

                new Ident<EModiType>(20, EModiType.Player_StandbyTime, "Standby Time"),
                new Ident<EModiType>(21, EModiType.Player_SleepTime, "Sleep Time"),
                new Ident<EModiType>(22, EModiType.Player_Volume, "Volume"),
                new Ident<EModiType>(23, EModiType.Player_VolumeUp, "Volume Up"),
                new Ident<EModiType>(24, EModiType.Player_VolumeDown, "Volume Down"),

                new Ident<EModiType>(30, EModiType.Player_Random, "Play Random"),
                new Ident<EModiType>(31, EModiType.Player_RepeatSingle, "Repeat Single Track"),
                new Ident<EModiType>(32, EModiType.Player_RepeatAll, "Repeat All Tracks"),
                new Ident<EModiType>(33, EModiType.Player_ListenToEnd, "Listen To End"),
                new Ident<EModiType>(34, EModiType.Player_StopOnCardRemoval, "Stop On Card Removal"),

                new Ident<EModiType>(40, EModiType.Player_FreezeDance, "Freeze Dance"),
                new Ident<EModiType>(41, EModiType.Player_MemoryMode, "Memory Mode"),
                new Ident<EModiType>(42, EModiType.Player_RandomQuiz, "Random Quiz"),

                new Ident<EModiType>(50, EModiType.LockAll, "Lock All"),
                new Ident<EModiType>(51, EModiType.LockButtons, "Lock Buttons"),

                new Ident<EModiType>(60, EModiType.SetupCard, "Setup Card"),
                new Ident<EModiType>(61, EModiType.ResetCard, "Reset Card"),
                new Ident<EModiType>(62, EModiType.ResetEEPROM, "Reset EEPROM"),

                new Ident<EModiType>(70, EModiType.MENU_ChangeSmall, "Menu Change Small"),
                new Ident<EModiType>(71, EModiType.MENU_ChangeLarge, "Menu Change Large"),
                new Ident<EModiType>(72, EModiType.MENU_Choose, "Menu Choose"),
                new Ident<EModiType>(73, EModiType.MENU_Cancel, "Menu Cancel"),
            };
        }

        public bool IsMinutesValue => Ident.Value == EModiType.Player_SleepTime ||
                                      Ident.Value == EModiType.Player_StandbyTime;

        public bool IsBool
        {
            get
            {
                switch (Ident.Value)
                {
                    case EModiType.TrackContinue:
                    case EModiType.Player_Random:
                    case EModiType.Player_RepeatSingle:
                    case EModiType.Player_RepeatAll:
                    case EModiType.Player_ListenToEnd:
                    case EModiType.Player_StopOnCardRemoval:
                    case EModiType.Player_FreezeDance:
                    case EModiType.Player_MemoryMode:
                    case EModiType.Player_RandomQuiz:
                    case EModiType.LockAll:
                    case EModiType.LockButtons: return true;
                }
                return false;
            }
        }

        public bool RequiresValue
        {
            get
            {
                if (IsBool)
                {
                    return true;
                }
                switch (Ident.Value)
                {
                    case EModiType.ShortCut:
                    case EModiType.Advertisement:
                    case EModiType.Player_StandbyTime:
                    case EModiType.Player_SleepTime:
                    case EModiType.Player_Volume: return true;
                }
                return false;
            }
        }

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
