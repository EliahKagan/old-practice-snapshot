#!/usr/bin/env python2

class Solution(object):
    def circularArrayLoop(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        print 'Looking for loop in %s.' % nums
        length = len(nums)
        
        def nextpos(pos):
            ret = (pos + nums[pos]) % length
            print 'At %s, the next position is %d.' % (nums, ret)
            return ret
        
        def erasePath(start, end):
            print 'Erasing path from %d until %d.' % (start, end)
            while start != end:
                nums[start], start = 0, nextpos(start)
        
        def findCycle(forward):
            if forward:
                def valid(pos):
                    print 'Checking that nums[%d] -> %d is positive.' \
                          % (pos, nums[pos])
                    return nums[pos] > 0
            else:
                def valid(pos):
                    print 'Checking that nums[%d] -> %d is negative.' \
                          % (pos, nums[pos])
                    return nums[pos] < 0
            
            def tryPath(head):
                print 'Trying path from %d.' % head
                
                # Tortoise and hare algorithm.
                slow = fast = head
                foundCycle = False

                print 'The first fast (hare) position will be %d.' % fast
                while valid(fast):
                    print 'The fast (hare) position is %d.' % fast
                    
                    # fast advances by two and checks for the end of the path
                    fast = nextpos(fast)
                    if not valid(fast):
                        break
                    fast = nextpos(fast)
                    
                    # slow advances by one and checks for overlap with fast
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

s = Solution()
a = [2, -1, 1, 2, 2]
s.circularArrayLoop(a)
