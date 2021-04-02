
using System.Collections.Generic;

namespace Tonuino_RFID_Tool
{
    public enum EMusicMode
    {
        None,
        RandomSingle,
        Album,
        Party,
        Single,
        Audiobook,
        Section_RandomSingle,
        Section_Album,
        Section_Party,
        Section_Audiobook,
        RandomFolder_Album,
        RandomFolder_Party,
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
                new Ident<EMusicMode>(1, EMusicMode.RandomSingle, "Random Single"),
                new Ident<EMusicMode>(2, EMusicMode.Album, "Album"),
                new Ident<EMusicMode>(3, EMusicMode.Party, "Party"),
                new Ident<EMusicMode>(4, EMusicMode.Single, "Single"),
                new Ident<EMusicMode>(5, EMusicMode.Audiobook, "Audiobook"),
                new Ident<EMusicMode>(7, EMusicMode.Section_RandomSingle, "Section - Random Single"),
                new Ident<EMusicMode>(8, EMusicMode.Section_Album, "Section - Album"),
                new Ident<EMusicMode>(9, EMusicMode.Section_Party, "Section - Party"),
                new Ident<EMusicMode>(10, EMusicMode.Section_Audiobook, "Section - Audiobook"),
                new Ident<EMusicMode>(11, EMusicMode.RandomFolder_Album, "Random Folder - Album"),
                new Ident<EMusicMode>(12, EMusicMode.RandomFolder_Party, "Random Folder - Party"),
            };
        }

        public bool UseStartEndTrack
        {
            get
            {
                switch (Ident.Value)
                {
                    case EMusicMode.Section_Album:
                    case EMusicMode.Section_RandomSingle:
                    case EMusicMode.Section_Party:
                    case EMusicMode.Section_Audiobook: return true;
                }
                return false;
            }
        }

        public bool UseDefinedSingleTrack => Ident.Value == EMusicMode.Single;
        public bool UseEndFolder
        {
            get
            {
                switch (Ident.Value)
                {
                    case EMusicMode.RandomSingle:
                    case EMusicMode.Album:
                    case EMusicMode.Party:
                    case EMusicMode.Audiobook:
                    case EMusicMode.RandomFolder_Album:
                    case EMusicMode.RandomFolder_Party: return true;
                }
                return false;
            }
        }

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
