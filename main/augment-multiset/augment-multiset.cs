internal static class DictionaryEx {
    internal static void Increase<T>(this Dictionary<T, int> multiset,
                                     T element, int delta)
    {
        int count;
        if (multiset.TryGetValue(element, out count))
            multiset[element] = count + delta;
        else multiset.Add(element, delta);
    }
}