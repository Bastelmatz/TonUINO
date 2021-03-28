
using System.Collections.Generic;
using System.Windows.Forms;

namespace Tonuino_RFID_Tool
{
    public class ExtendedComboBox : ComboBox
    {
        public void SetItems<T>(List<T> items)
        {
            Items.Clear();
            foreach (T item in items)
            {
                Items.Add(item);
            }
            SelectFirstEntry();
        }

        public void SelectFirstEntry()
        {
            if (Items.Count > 0)
            {
                SelectedItem = Items[0];
            }
        }

        public void SelectEntry<T>(BaseType<T> entry)
        {
            foreach (var item in Items)
            {
                if (item is BaseType<T>)
                {
                    BaseType<T> baseType = (BaseType<T>)item;
                    if (baseType == entry)
                    {
                        SelectedItem = item;
                        break;
                    }
                }
            }
        }
    }
}
