#!/usr/bin/env python2

class Solution(object):
    def circularArrayLoop(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        length = len(nums)

        def nextpos(pos):
            return (pos + nums[pos]) % length

        def erasePath(start, end):
            while start != end:
                nums[start], start = 0, nextpos(start)

        def findCycle(forward):
            if forward:
                def valid(pos):
                    return nums[pos] > 0
            else:
                def valid(pos):
                    return nums[pos] < 0

            def tryPath(head):
                # Tortoise and hare algorithm.
                slow = fast = head
                foundCycle = False

                while valid(fast):
                    # fast advances by two and checks for the end of the path
                    fast = nextpos(fast)
                    if not valid(fast):
                        break
                    fast = nextpos(fast)

                    # slow advancces by one and checks for overlap with fast
                    slow = nextpos(slow)
                    if slow == fast:
                        foundCycle = True
                        break

                if foundCycle:
                    if fast != nextpos(fast): # not a singleton, yay!
                        return True
                    nums[fast] = 0

                erasePath(head, fast)
                return False

            for head in xrange(length):
                if tryPath(head):
                    return True

            return False

        return findCycle(True) or findCycle(False)

def test(*nums):
    print Solution().circularArrayLoop(list(nums))

test(-2, 1, -1, -2, -2)
test(2, -1, -1)
test(2, -1, 1, 2, 2)
test(1, 1, 1, 1, 1, 1, 1)
test(-1, -1, -1, -1, -1, -1, -1)
test(1000)
test(1001)
test(1000, 1)
test(1001, 1)
test(1001, -1)
