class Solution:
    def escapeGhosts(self, ghosts, target):
        """
        :type ghosts: List[List[int]]
        :type target: List[int]
        :rtype: bool
        """
        def distance(thing):
            return abs(target[0] - thing[0]) + abs(target[1] - thing[1])
        
        player_distance = distance((0, 0))
        return all(distance(ghost) > player_distance for ghost in ghosts)
