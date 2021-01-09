
using System.Collections.Generic;

namespace Tonuino_RFID_Creator
{
    public enum EMusicMode
    {
        None,
        Hoerspiel,
        Album,
        Party,
        Einzel,
        Hoerbuch,
        SpezialVonBis_Hoerspiel,
        SpezialVonBis_Album,
        SpezialVonBis_Party,
    }

    public class MusicMode : BaseType<EMusicMode>
    {
        public MusicMode(EMusicMode mode) : base(mode)
        {

        }

        protected override void createAllocation()
        {
            m_allocation = new List<Ident<EMusicMode>>
            {
                new Ident<EMusicMode>(0, EMusicMode.None, ""),
                new Ident<EMusicMode>(1, EMusicMode.Hoerspiel, "Hörspiel"),
                new Ident<EMusicMode>(2, EMusicMode.Album, "Album"),
                new Ident<EMusicMode>(3, EMusicMode.Party, "Party"),
                new Ident<EMusicMode>(4, EMusicMode.Einzel, "Einzeln"),
                new Ident<EMusicMode>(5, EMusicMode.Hoerbuch, "Hörbuch"),
                new Ident<EMusicMode>(7, EMusicMode.SpezialVonBis_Hoerspiel, "Spezial von bis - Hörspiel"),
                new Ident<EMusicMode>(8, EMusicMode.SpezialVonBis_Album, "Spezial von bis - Album"),
                new Ident<EMusicMode>(9, EMusicMode.SpezialVonBis_Party, "Spezial von bis - Party"),
            };
        }

        public bool UseStartEndTrack
        {
            get
            {
                switch (Ident.Value)
                {
                    case EMusicMode.SpezialVonBis_Album:
                    case EMusicMode.SpezialVonBis_Hoerspiel:
                    case EMusicMode.SpezialVonBis_Party: return true;
                }
                return false;
            }
        }

        public bool UseSingleTrack => Ident.Value == EMusicMode.Einzel;

        public static List<MusicMode> AllValidModes()
        {
            List<EMusicMode> enumList = getEnumList();
            List<MusicMode> retList = new List<MusicMode>();
            foreach (EMusicMode mode in enumList)
            {
                if (mode != EMusicMode.None)
                {
                    retList.Add(new MusicMode(mode));
                }
            }
            return retList;
        }
    }
}
