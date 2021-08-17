#define DEBUG

using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;

internal sealed class LRU<T> : IEnumerable<T> {
    internal LRU(int capacity)
    {
        if (capacity <= 0) {
            throw new ArgumentOutOfRangeException(
                message: "capacity must be (strictly) positive",
                paramName: nameof(capacity));
        }
        
        Capacity = capacity;
    }
    
    internal int Capacity { get; }
    
    internal int Count => _chain.Count;
    
    public override string ToString() => string.Join(" ", this);
    
    public IEnumerator<T> GetEnumerator() => _chain.GetEnumerator();
    
    IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
    
    internal bool Bump(T key) // returns true iff a cache miss occurs
    {
        LinkedListNode<T> node;
        if (_table.TryGetValue(key, out node)) {
            MoveToHead(node);
            return false;
        }
        
        if (Count == Capacity) {
            node = _chain.Last;
            _table.Remove(node.Value);
            MoveToHead(node);
            node.Value = key;
        } else {
            Contract.Assert(Count < Capacity);
            node = _chain.AddFirst(key);
        }
        
        _table.Add(key, node);
        return true;
    }
    
    private void MoveToHead(LinkedListNode<T> node)
    {
        _chain.Remove(node);
        _chain.AddFirst(node);
    }

    private readonly Dictionary<T, LinkedListNode<T>> _table
            = new Dictionary<T, LinkedListNode<T>>();
    
    private readonly LinkedList<T> _chain = new LinkedList<T>();
}

internal static class Solution {
    private static void Main()
    {
        var ns = Array.ConvertAll(ReadTokens(), int.Parse);
        var cache = new LRU<int>(ns[1]);
        Console.WriteLine(ReadValues(ns[0]).Count(cache.Bump));
        Console.WriteLine(cache);
    }
    
    private static IEnumerable<int> ReadValues(int count)
    {
        while (count > 0) {
            foreach (var key in ReadTokens().Select(int.Parse)) {
                yield return key;
                if (--count == 0) break;
            }
        }
    }
    
    private static string[] ReadTokens()
        => Console.ReadLine().Split((char[])null,
                                    StringSplitOptions.RemoveEmptyEntries);
}
