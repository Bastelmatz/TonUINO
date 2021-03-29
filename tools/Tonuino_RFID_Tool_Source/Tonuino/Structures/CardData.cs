
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace Tonuino_RFID_Tool
{
    public interface IMusicCardData
    {
        byte Raw_Mode { get; }
        byte Raw_Folder { get; }
        byte Raw_Special { get; }
        byte Raw_Special2 { get; }
    }

    public class MusicCardDataRaw : IMusicCardData
    {
        public byte Raw_Mode { get; set; }
        public byte Raw_Folder { get; set; }
        public byte Raw_Special { get; set; }
        public byte Raw_Special2 { get; set; }
    }

    public interface IModiCardData
    {
        byte Raw_Mode { get; }
        ushort Raw_Value { get; }
    }

    public class ModiCardDataRaw : IModiCardData
    {
        public byte Raw_Mode { get; set; }
        public ushort Raw_Value { get; set; }
    }

    public class CardData
    {
        public long RFID { get; }
        public int Cookie { get; }

        public bool Exists => RFID != 0;

        public static int MAXBYTES { get; } = 16;

        // magic cookie, software version
        public static ReadOnlyCollection<byte> FirstTonuinoBytes { get; } = new List<byte> { 19, 55, 179, 71, 2 }.AsReadOnly(); 
        private static int tonuinoCookie { get; } = 322417479; // 0x1337 0xb347 // 19|55|179|71
        public bool IsNewCard => Cookie != tonuinoCookie;
        public string RFIDHex => RFID.ToString("X");

        public CardData() : this (0, 0)
        { }

        public CardData(long rfid, int cookie)
        {
            RFID = rfid;
            Cookie = cookie;
        }
    }

    public class MusicCardData : CardData, IMusicCardData
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

    public class LegacyModiCardData : CardData
    {
        public LegacyModiType ModiType { get; }
        public TimeSpan SleepTime { get; }

        public int Raw_Mode => ModiType.Index;
        public int Raw_Folder => 0;
        public int Raw_Special => ModiType.UseSleepTimeSetting ? SleepTime.Minutes : 0;
        public int Raw_Special2 => 0;

        public LegacyModiCardData(long rfid, int cookie, ELegacyModiType modiType, TimeSpan sleepTime) 
            : base (rfid, cookie)
        {
            ModiType = new LegacyModiType(modiType);
            SleepTime = sleepTime;
        }
    }

    public class ModiCardData : CardData
    {
        public ModiType ModiType { get; }
        public ushort Value { get; }

        public int Raw_Mode => ModiType.Index;
        public int Raw_Special => Value;

        public ModiCardData(long rfid, int cookie, EModiType modiType, ushort value)
            : base(rfid, cookie)
        {
            ModiType = new ModiType(modiType);
            Value = value;
        }
    }
}
