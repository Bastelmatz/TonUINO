
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace Tonuino_RFID_Tool
{
    public interface IMusicCardData
    {
        byte Raw_Mode { get; }
        byte Raw_StartFolder { get; }
        ushort Raw_Special { get; }
        ushort Raw_Special2 { get; }
        byte Raw_EndFolder { get; }
        ushort Raw_RecentTrack { get; }
        byte Raw_RecentFolder { get; }

        bool IsAdvertisement_Start { get; }
        bool IsAdvertisement_End { get; }
    }

    public class MusicCardDataRaw : IMusicCardData
    {
        public byte Raw_Mode { get; set; }
        public byte Raw_StartFolder { get; set; }
        public ushort Raw_Special { get; set; }
        public ushort Raw_Special2 { get; set; }
        public byte Raw_EndFolder { get; set; }
        public ushort Raw_RecentTrack { get; set; }
        public byte Raw_RecentFolder { get; set; }

        public bool IsAdvertisement_Start => Raw_StartFolder == CardData.FOLDER_ADVERTISEMENT;
        public bool IsAdvertisement_End => Raw_EndFolder == CardData.FOLDER_ADVERTISEMENT;
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

        public static int FOLDER_ADVERTISEMENT = 100;
        public static int MAX_FOLDER { get; } = 100; // 0-99 folder with respective name, 100 advertisement
        public static int MAX_TRACK { get; } = 255;
        public static int MAX_TRACK_LARGE { get; } = 3000;
        public static int GetMaxTrack(int folder) => folder < 16 || folder == FOLDER_ADVERTISEMENT ? MAX_TRACK_LARGE : MAX_TRACK;

        // magic cookie, software version
        public static ReadOnlyCollection<byte> FirstTonuinoBytes { get; } = new List<byte> { 19, 55, 179, 71, tonuinoVersion }.AsReadOnly(); 
        private static int tonuinoCookie { get; } = 322417479; // 0x1337 0xb347 // 19|55|179|71
        private const byte tonuinoVersion = 2;

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
        public byte StartFolder { get; }
        public ushort StartPos { get; }
        public ushort EndPos { get; }
        public byte EndFolder { get; }
        public ushort RecentTrack { get; }
        public byte RecentFolder { get; }

        public byte Raw_Mode => Mode.Index;
        public byte Raw_StartFolder => StartFolder;
        public ushort Raw_Special => StartPos;
        public ushort Raw_Special2 => EndPos;
        public byte Raw_EndFolder => EndFolder;
        public ushort Raw_RecentTrack => RecentTrack;
        public byte Raw_RecentFolder => RecentFolder;

        public bool IsAdvertisement_Start => Raw_StartFolder == FOLDER_ADVERTISEMENT;
        public bool IsAdvertisement_End => Raw_EndFolder == FOLDER_ADVERTISEMENT;

        public MusicCardData(long rfid, int cookie, EMusicMode mode, byte folder, ushort startPos, ushort endPos, byte endFolder, ushort recentTrack, byte recentFolder)
            : base (rfid, cookie)
        {
            Mode = new MusicMode(mode);
            StartFolder = folder;
            StartPos = startPos;
            EndPos = endPos;
            EndFolder = endFolder;
            RecentTrack = recentTrack;
            RecentFolder = recentFolder;
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

        public byte Raw_Mode => ModiType.Index;
        public ushort Raw_Special => Value;

        public ModiCardData(long rfid, int cookie, EModiType modiType, ushort value)
            : base(rfid, cookie)
        {
            ModiType = new ModiType(modiType);
            Value = value;
        }
    }
}
