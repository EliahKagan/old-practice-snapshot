class RandomizedCollection:
    def __init__(self):
        """
        Initialize your data structure here.
        """
        self._elems = []
        self._indexTable = {}

    def insert(self, val):
        """
        Inserts a value to the collection. Returns true if the collection did not already contain the specified element.
        :type val: int
        :rtype: bool
        """
        # The value will be inserted at the end of the list.
        valIndex = len(self._elems)
        self._elems.append(val)

        # Update the index-tracking table. Check if it holds any other
        # indices to elements of the same value and return that information.
        try:
            valIndices = self._indexTable[val]
            wasEmpty = not valIndices
            valIndices.add(valIndex)
            return wasEmpty
        except KeyError:
            self._indexTable[val] = {valIndex}
            return True

    def remove(self, val):
        """
        Removes a value from the collection. Returns true if the collection contained the specified element.
        :type val: int
        :rtype: bool
        """
        # If we have the value, find and remove some index to it.
        try:
            valIndex = self._indexTable[val].pop()
        except KeyError:
            return False

        # Remove the back element.
        other = self._elems.pop()
        otherIndex = len(self._elems)

        # If the element we wish to remove is not the back element...
        if valIndex != otherIndex:
            # ...then copy the back element to the newly vacted position.
            self._elems[valIndex] = other

            # ...and update the index-tracking table accordingly.
            otherIndices = self._indexTable[other]
            otherIndices.remove(otherIndex)
            otherIndices.add(valIndex)

        return True


    def getRandom(self):
        """
        Get a random element from the collection.
        :rtype: int
        """
        return self._elems[random.randint(0, len(self._elems) - 1)]


# Your RandomizedCollection object will be instantiated and called as such:
# obj = RandomizedCollection()
# param_1 = obj.insert(val)
# param_2 = obj.remove(val)
# param_3 = obj.getRandom()
