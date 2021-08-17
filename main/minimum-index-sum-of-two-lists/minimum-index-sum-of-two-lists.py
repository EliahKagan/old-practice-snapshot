class Solution:
    def findRestaurant(self, list1, list2):
        """
        :type list1: List[str]
        :type list2: List[str]
        :rtype: List[str]
        """
        inverse1 = {e: i for i, e in enumerate(list1)}
        overlap = collections.defaultdict(list) # stored by index sum

        for j, e in enumerate(list2):
            try:
                overlap[inverse1[e] + j].append(e)
            except KeyError:
                pass

        return overlap[min(overlap)]
