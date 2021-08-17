class RandomizedCollection {
    /** Initialize your data structure here. */
    public RandomizedCollection() {

    }

    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    public boolean insert(int val) {

    }

    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    public boolean remove(final int val) {
        // Check if we even have the value.
        final List<Integer> indices = _indexTable.get(val);
        if (indices == null || indices.isEmpty()) return false;

        // Find and remove an index to the value.
        final int metaIndex = indices.size() - 1;
        final int index = indices.get(metaIndex);
        indices.remove(metaIndex);

        // Swap the value with the last element and pop it from the list.
    }

    /** Get a random element from the collection. */
    public int getRandom() {
        return _elems.get(_randomGenerator.nextInt(_elems.size()));
    }

    private final List<Integer> _elems = new ArrayList<>();

    // FIXME: probably need to use Map<Integer, Set<Integer>> instead (with HashSet<>)
    private final Map<Integer, List<Integer>> _indexTable = new HashMap<>();

    private final Random _randomGenerator = new Random();
}

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * boolean param_1 = obj.insert(val);
 * boolean param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
