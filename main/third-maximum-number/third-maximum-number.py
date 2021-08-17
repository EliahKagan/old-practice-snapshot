class Solution:
    def thirdMax(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        fst = snd = thd = None

        for x in nums:
            if x == fst or x == snd or x == thd:
                continue

            if fst is None or x > fst:
                thd = snd
                snd = fst
                fst = x
            elif snd is None or x > snd:
                thd = snd
                snd = x
            elif thd is None or x > thd:
                thd = x

        return fst if thd is None else thd
