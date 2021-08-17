import contextlib

LEXER = re.compile(r'[*/+-]|\d+')

def divide(dividend, divisor):
    return math.trunc(dividend / divisor)

class Solution:
    def calculate(self, s):
        """
        :type s: str
        :rtype: int
        """
        outer_acc = 0
        inner_acc = 1
        outer_fn = operator.add
        inner_fn = operator.mul

        it = iter(LEXER.findall(s))
        with contextlib.suppress(StopIteration):
            while True:
                tok = next(it)
                if tok in '+-':
                    # print(outer_acc, outer_fn, inner_acc)
                    outer_acc = outer_fn(outer_acc, inner_acc)
                    outer_fn = operator.add if tok == '+' else operator.sub
                    inner_acc = 1
                    inner_fn = operator.mul
                elif tok in '*/':
                    inner_fn = operator.mul if tok == '*' else divide
                else:
                    # print(inner_acc, inner_fn, tok)
                    inner_acc = inner_fn(inner_acc, int(tok))

        return outer_fn(outer_acc, inner_acc)
