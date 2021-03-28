
using System.Collections.Generic;

namespace Tonuino_RFID_Tool
{
    public enum EModiBoolValue
    {
        None,
        Set,
        Undo,
        Toggle,
        
        OnRemoval_Set,
        OnRemoval_Undo,
        OnRemoval_Toggle,

        Set_OnRemoval_Undo,
        Undo_OnRemoval_Set,
        Toggle_OnRemoval_Toggle,
    }

    public class ModiBoolValue : BaseType<EModiBoolValue>
    {
        public ModiBoolValue(EModiBoolValue modiBoolValue) : base(modiBoolValue)
        {

        }

        protected override void createAllocation()
        {
            m_allocation = new List<Ident<EModiBoolValue>>
            {
                new Ident<EModiBoolValue>(0, EModiBoolValue.None, ""),
                new Ident<EModiBoolValue>(1, EModiBoolValue.Set, "Set"),
                new Ident<EModiBoolValue>(2, EModiBoolValue.Undo, "Undo"),
                new Ident<EModiBoolValue>(3, EModiBoolValue.Toggle, "Toggle"),

                new Ident<EModiBoolValue>(10, EModiBoolValue.OnRemoval_Set, "Set on removal"),
                new Ident<EModiBoolValue>(11, EModiBoolValue.OnRemoval_Undo, "Undo on removal"),
                new Ident<EModiBoolValue>(11, EModiBoolValue.OnRemoval_Toggle, "Toggle on removal"),

                new Ident<EModiBoolValue>(20, EModiBoolValue.Set_OnRemoval_Undo, "Set, Undo on removal"),
                new Ident<EModiBoolValue>(21, EModiBoolValue.Undo_OnRemoval_Set, "Undo, Set on removal"),
                new Ident<EModiBoolValue>(22, EModiBoolValue.Toggle_OnRemoval_Toggle, "Toggle, also on removal"),
            };
        }

        public static List<ModiBoolValue> AllValidValues()
        {
            List<EModiBoolValue> enumList = getEnumList();
            List<ModiBoolValue> retList = new List<ModiBoolValue>();
            foreach (EModiBoolValue modiValue in enumList)
            {
                if (modiValue != EModiBoolValue.None)
                {
                    retList.Add(new ModiBoolValue(modiValue));
                }
            }
            return retList;
        }
    }
}
