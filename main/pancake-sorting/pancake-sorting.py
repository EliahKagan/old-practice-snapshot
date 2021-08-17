class Solution:
    def pancakeSort(self, a):
        """
        :type A: List[int]
        :rtype: List[int]
        """
        a = a[:]
        ks = []

        def flip(k):
            a[:k] = reversed(a[:k])
            ks.append(k)

        for length in range(len(a), 0, -1):
            big_value = max(a[:length])
            big_index = a.index(big_value)
            flip(big_index + 1)  # bring the maximum to the front
            flip(length)  # then flip it all the way to the end

        assert a == sorted(a)
        return ks
