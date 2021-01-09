
using System;
using System.Collections.Generic;
using System.Linq;

namespace Tonuino_RFID_Creator
{
    public class Ident<T>
    {
        public int Index { get; }
        public T Value { get; }
        public string NameString { get; }

        public Ident(int index, T value, string name)
        {
            Index = index;
            Value = value;
            NameString = name;
        }
    }

    public abstract class BaseType<T>
    {
        public Ident<T> Ident { get; }

        private static bool allocationCreated = false;
        protected static List<Ident<T>> m_allocation { get; set; } = new List<Ident<T>>();

        public BaseType(T value)
        {
            if (!allocationCreated)
            {
                createAllocation();
                if (m_allocation.Count == 0)
                {
                    throw new Exception("No allocation defined");
                }
                allocationCreated = true;
            }

            foreach (Ident<T> ident in m_allocation)
            {
                if (ident.Value.Equals(value))
                {
                    Ident = ident;
                    break;
                }
            }
        }

        protected abstract void createAllocation();



        public static T FromNumber(int number)
        {
            foreach (Ident<T> ident in m_allocation)
            {
                if (ident.Index == number)
                {
                    return ident.Value;
                }
            }
            return m_allocation[0].Value;
        }

        public int Index => Ident.Index;

        public string Name => Ident.NameString;

        public override string ToString()
        {
            return Index + " - " + Name;
        }

        public static bool operator ==(BaseType<T> obj1, BaseType<T> obj2)
        {
            if (ReferenceEquals(obj1, obj2))
            {
                return true;
            }
            if (ReferenceEquals(obj1, null))
            {
                return false;
            }
            if (ReferenceEquals(obj2, null))
            {
                return false;
            }

            return obj1.Equals(obj2);
        }

        public static bool operator !=(BaseType<T> obj1, BaseType<T> obj2)
        {
            return !(obj1 == obj2);
        }

        public override bool Equals(object obj)
        {
            return Equals(obj as BaseType<T>);
        }

        public bool Equals(BaseType<T> other)
        {
            if (ReferenceEquals(other, null))
            {
                return false;
            }
            if (ReferenceEquals(this, other))
            {
                return true;
            }

            return Ident.Value.Equals(other.Ident.Value);
        }

        public override int GetHashCode()
        {
            return Ident.Value.GetHashCode();
        }

        protected static List<T> getEnumList()
        {
            return Enum.GetValues(typeof(T)).Cast<T>().ToList();
        }
    }
}
