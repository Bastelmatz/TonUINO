
using System;

namespace Tonuino_RFID_Creator
{
    public class AdminSettings
    {
        public int MinVolume { get; }
        public int MaxVolume { get; }
        public int InitVolume { get; }
        public TimeSpan StandbyTime { get; }
        public EqualizerType Equalizer { get; }

        public bool Exists => MaxVolume > 0;

        public AdminSettings() : this (0, 0, 0, TimeSpan.FromMinutes(0), EEqualizerType.Normal)
        { }

        public AdminSettings(int minVol, int initVol, int maxVol, TimeSpan standbyTime, EEqualizerType equalizer)
        {
            MinVolume = minVol;
            InitVolume = initVol;
            MaxVolume = maxVol;
            StandbyTime = standbyTime;
            Equalizer = new EqualizerType(equalizer);
        }
    }
}
