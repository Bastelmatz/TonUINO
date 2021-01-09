
using System;

namespace Tonuino_RFID_Creator
{
    public interface ICardData
    {
        byte Raw_Mode { get; }
        byte Raw_Folder { get; }
        byte Raw_Special { get; }
        byte Raw_Special2 { get; }
    }

    public class CardDataRaw : ICardData
    {
        public byte Raw_Mode { get; set; }
        public byte Raw_Folder { get; set; }
        public byte Raw_Special { get; set; }
        public byte Raw_Special2 { get; set; }
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
        public byte Folder { get; }
        public byte StartPos { get; }
        public byte EndPos { get; }

        public byte Raw_Mode => Mode.Index;
        public byte Raw_Folder => Folder;
        public byte Raw_Special => StartPos;
        public byte Raw_Special2 => EndPos;

        public MusicCardData(long rfid, int cookie, EMusicMode mode, byte folder, byte startPos, byte endPos)
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
