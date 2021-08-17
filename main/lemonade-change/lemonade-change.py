class Solution:
    def lemonadeChange(self, bills):
        """
        :type bills: List[int]
        :rtype: bool
        """
        fives = tens = 0
        
        for bill in bills:
            if bill == 5:
                fives += 1
            elif bill == 10:
                if fives:
                    fives -= 1
                    tens += 1
                else:
                    return False
            elif bill == 20:
                if fives and tens:
                    fives -= 1
                    tens -= 1
                elif fives >= 3:
                    fives -= 3
                else:
                    return False
            else:
                raise ValueError('bill must be 5, 10, or 20')
        
        return True
