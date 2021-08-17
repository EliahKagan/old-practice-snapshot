HIGH_BIT = 128
MAX_CODEPOINT_WIDTH = 4
FOLLOW_MASK = HIGH_BIT | (HIGH_BIT >> 1)

class Solution:
    def validUtf8(self, data):
        """
        :type data: List[int]
        :rtype: bool
        """
        i = 0
        length = len(data)
        while i != length:
            elem = data[i]

            zpos = 0
            while elem & (HIGH_BIT >> zpos):
                zpos += 1

            if zpos == 0:
                i += 1
                continue

            if zpos == 1 or zpos > MAX_CODEPOINT_WIDTH:
                return False

            j = i + zpos
            if j > length:
                return False

            i += 1
            while i != j:
                if data[i] & FOLLOW_MASK != HIGH_BIT:
                    return False
                i += 1

        return True
