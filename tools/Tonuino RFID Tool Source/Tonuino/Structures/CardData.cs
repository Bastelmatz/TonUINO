
using System;

namespace Tonuino_RFID_Creator
{
    public interface ICardData
    {
        int Raw_Mode { get; }
        int Raw_Folder { get; }
        int Raw_Special { get; }
        int Raw_Special2 { get; }
    }

    public class CardData
    {
        public long RFID { get; }
        public int Cookie { get; }

        public bool Exists => RFID != 0;
        private static int TonuinoCookie { get; } = 322417479;
        public bool IsNewCard => Cookie != TonuinoCookie;
        public string RFIDHex => RFID.ToString("X");

        public CardData() : this (0, 0)
        { }

        public CardData(long rfid, int cookie)
        {
            RFID = rfid;
            Cookie = cookie;
        }
    }

    public class MusicCardData : CardData, ICardData
    {
        public MusicMode Mode { get; }
        public int Folder { get; }
        public int StartPos { get; }
        public int EndPos { get; }

        public int Raw_Mode => Mode.Index;
        public int Raw_Folder => Folder;
        public int Raw_Special => StartPos;
        public int Raw_Special2 => EndPos;

        public MusicCardData(long rfid, int cookie, EMusicMode mode, int folder, int startPos, int endPos)
            : base (rfid, cookie)
        {
            Mode = new MusicMode(mode);
            Folder = folder;
            StartPos = startPos;
            EndPos = endPos;
        }
    }

    public class ModiCardData : CardData
    {
        public ModiType ModiType { get; }
        public TimeSpan SleepTime { get; }

        public int Raw_Mode => ModiType.Index;
        public int Raw_Folder => 0;
        public int Raw_Special => ModiType.UseSleepTimeSetting ? SleepTime.Minutes : 0;
        public int Raw_Special2 => 0;

        public ModiCardData(long rfid, int cookie, EModiType modiType, TimeSpan sleepTime) 
            : base (rfid, cookie)
        {
            ModiType = new ModiType(modiType);
            SleepTime = sleepTime;
        }
    }
}
