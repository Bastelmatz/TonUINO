
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
        UniDirectionalPair,
        BiDirectionalPair,
        RandomUniDirectionalPair,
        RandomBiDirectionalPair,
        Section_RandomUniDirectionalPair,
        Section_RandomBiDirectionalPair
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
                new Ident<EMusicMode>(20, EMusicMode.RandomFolder_Album, "Random Folder - Album"),
                new Ident<EMusicMode>(21, EMusicMode.RandomFolder_Party, "Random Folder - Party"),
                new Ident<EMusicMode>(30, EMusicMode.UniDirectionalPair, "Uni-Directional Pair"),
                new Ident<EMusicMode>(31, EMusicMode.BiDirectionalPair, "Bi-Directional Pair"),
                new Ident<EMusicMode>(35, EMusicMode.RandomUniDirectionalPair, "Random Uni-Directional Pair"),
                new Ident<EMusicMode>(36, EMusicMode.RandomBiDirectionalPair, "Random Bi-Directional Pair"),
                new Ident<EMusicMode>(37, EMusicMode.Section_RandomUniDirectionalPair, "Section - Random Uni-Directional Pair"),
                new Ident<EMusicMode>(38, EMusicMode.Section_RandomBiDirectionalPair, "Section - Random Bi-Directional Pair"),
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
                    case EMusicMode.Section_Audiobook:
                    case EMusicMode.Section_RandomUniDirectionalPair:
                    case EMusicMode.Section_RandomBiDirectionalPair: return true;
                }
                return false;
            }
        }

        public bool UseDefinedSingleTrack
        {
            get
            {
                switch (Ident.Value)
                {
                    case EMusicMode.Single:
                    case EMusicMode.UniDirectionalPair:
                    case EMusicMode.BiDirectionalPair: return true;
                }
                return false;
            }
        }

        public bool UseCompareFolder
        {
            get
            {
                switch (Ident.Value)
                {
                    case EMusicMode.UniDirectionalPair:
                    case EMusicMode.BiDirectionalPair:
                    case EMusicMode.RandomUniDirectionalPair:
                    case EMusicMode.RandomBiDirectionalPair:
                    case EMusicMode.Section_RandomUniDirectionalPair:
                    case EMusicMode.Section_RandomBiDirectionalPair: return true;
                }
                return false;
            }
        }

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
                if (UseCompareFolder)
                {
                    return true;
                }
                return false;
            }
        }

        public bool UseRecentTrackAndFolder
        {
            get
            {
                switch (Ident.Value)
                {
                    case EMusicMode.Audiobook:
                    case EMusicMode.Section_Audiobook: return true;
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
