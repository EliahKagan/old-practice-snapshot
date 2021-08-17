#define DEBUG

using System;
using System.Diagnostics.Contracts;
using System.Linq;

internal struct Order : IEquatable<Order>, IComparable<Order> {
    private static int Customers = 0;

    public readonly int CustomerId; // we consider the default value 0 invalid
    public readonly int ReadyTime;

    public Order(int time, int delay)
    {
        checked {
            CustomerId = ++Customers; // indexes from 1 as in problem statement
            ReadyTime = time + delay;
        }
    }

    public override int GetHashCode()
    {
        return CustomerId;
    }

    public override bool Equals(object obj)
    {
        Contract.Assert(CustomerId > 0);
        var other = obj as Order?;
        return other.HasValue && ((IEquatable<Order>)this).Equals(other.Value);
    }

    bool IEquatable<Order>.Equals(Order other)
    {
        Contract.Assert(CustomerId > 0);
        return CustomerId == other.CustomerId && ReadyTime == other.ReadyTime;
    }

    int IComparable<Order>.CompareTo(Order other)
    {
        Contract.Assert(CustomerId > 0);
        var compare_ready = ReadyTime - other.ReadyTime;
        return compare_ready == 0 ? CustomerId - other.CustomerId
                                  : compare_ready;
    }
}

internal static class Orders {
    public static Order GetOne()
    {
        var td = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        return new Order(td[0], td[1]);
    }

    public static Order[] GetAll(int n)
    {
        var orders = new Order[n];
        foreach (var i in Enumerable.Range(0, n)) orders[i] = GetOne();
        return orders;
    }
}

internal static class Solution {
    private static void Main()
    {
        var orders = Orders.GetAll(int.Parse(Console.ReadLine()));
        Array.Sort(orders);

        var sep = string.Empty;
        foreach (var order in orders) {
            Console.Write("{0}{1}", sep, order.CustomerId);
            sep = " ";
        }

        Console.WriteLine();
    }
}
