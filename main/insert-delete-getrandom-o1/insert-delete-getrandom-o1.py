class RandomizedSet:
    def __init__(self):
        """
        Initialize your data structure here.
        """
        self._elems = []
        self._lookup = {}


    def insert(self, val):
        """
        Inserts a value to the set. Returns true if the set did not already contain the specified element.
        :type val: int
        :rtype: bool
        """
        if val in self._lookup:
            return False

        self._lookup[val] = len(self._elems)
        self._elems.append(val)
        return True

    def remove(self, val):
        """
        Removes a value from the set. Returns true if the set contained the specified element.
        :type val: int
        :rtype: bool
        """
        try:
            valIndex = self._lookup.pop(val)
        except KeyError:
            return False

        other = self._elems.pop()

        if valIndex != len(self._elems):
            self._elems[valIndex] = other
            self._lookup[other] = valIndex

        return True

    def getRandom(self):
        """
        Get a random element from the set.
        :rtype: int
        """
        return random.choice(self._elems)


# Your RandomizedSet object will be instantiated and called as such:
# obj = RandomizedSet()
# param_1 = obj.insert(val)
# param_2 = obj.remove(val)
# param_3 = obj.getRandom()
