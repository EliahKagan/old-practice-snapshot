from fractions import Fraction

BASE = 10

PATTERN = re.compile(r'(?P<IntegerPart>\d*)\.'
                     r'(?P<NonRepeatingPart>\d*)'
                     r'\((?P<RepeatingPart>\d+)\)')

def parse_int(s):
    return int(s) if s else 0

def parse_fraction(s):
    try:
        return Fraction(s)
    except ValueError:
        m = PATTERN.match(s)

        i = m.group('IntegerPart')
        d = m.group('NonRepeatingPart')
        r = m.group('RepeatingPart')

        place = BASE**len(d)

        return (parse_int(i) + Fraction(parse_int(d), place)
                             + Fraction(int(r), (BASE**len(r) - 1) * place))

class Solution:
    @staticmethod
    def isRationalEqual(s, t):
        """
        :type S: str
        :type T: str
        :rtype: bool
        """
        return parse_fraction(s) == parse_fraction(t)
