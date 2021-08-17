class Solution:
    def uniqueOccurrences(self, arr: List[int]) -> bool:
        freqs = collections.Counter(arr)
        return len(set(freqs.values())) == len(freqs)
