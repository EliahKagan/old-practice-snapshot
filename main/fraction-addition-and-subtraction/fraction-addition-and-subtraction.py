import fractions

FRACTION_PATTERN = re.compile(r'[+-]\d+/\d+')

class Solution:
    def fractionAddition(self, expression):
        """
        :type expression: str
        :rtype: str
        """
        if expression[0].isdigit():
            expression = '+' + expression
        tokens = FRACTION_PATTERN.finditer(expression)
        result = sum(fractions.Fraction(match.group()) for match in tokens)
        return '{}/{}'.format(result.numerator, result.denominator)
