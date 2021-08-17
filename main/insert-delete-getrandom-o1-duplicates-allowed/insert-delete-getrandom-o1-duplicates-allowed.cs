public sealed class RandomizedCollection {
    /// Inserts a value to the collection. Returns true if the collection did not already contain the specified element.
    public bool Insert(int val) {
        // The value will be inserted at the end of the list.
        var valIndex = _elems.Count;
        _elems.Add(val);

        // Update the index-tracking table. Check if it holds any other
        // indices to elements of the same value and return that information.
        if (_indexTable.TryGetValue(val, out var valIndices)) {
            valIndices.Add(valIndex);
            return valIndices.Count == 1;
        } else {
            _indexTable.Add(val, new HashSet<int> { valIndex });
            return true;
        }
    }

    /// Removes a value from the collection. Returns true if the collection contained the specified element.
    public bool Remove(int val) {
        // Check if we even have the value.
        if (!_indexTable.TryGetValue(val, out var valIndices)
                || valIndices.Count == 0)
            return false;

        // Find an index to an occurrence of the value. Any such index is fine.
        var valIndex = valIndices.First();
        valIndices.Remove(valIndex);

        // The current back element might not be what we want to remove.
        var otherIndex = _elems.Count - 1;

        // If the back element isn't the one we wish to remove...
        if (valIndex != otherIndex) {
            // ...then copy it to the newly vacated position.
            var other = _elems[otherIndex];
            _elems[valIndex] = other;

            // ...and update the index-tracking table accordingly.
            var otherIndices = _indexTable[other];
            otherIndices.Remove(otherIndex);
            otherIndices.Add(valIndex);
        }

        // Pop off the back element.
        _elems.RemoveAt(otherIndex);
        return true;
    }

    /// Get a random element from the collection.
    public int GetRandom() => _elems[_randomGenerator.Next(_elems.Count)];

    private readonly List<int> _elems = new List<int>();

    private readonly Dictionary<int, HashSet<int>> _indexTable =
            new Dictionary<int, HashSet<int>>();

    private readonly Random _randomGenerator = new Random();
}

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.Insert(val);
 * bool param_2 = obj.Remove(val);
 * int param_3 = obj.GetRandom();
 */
