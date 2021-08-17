LEXER = re.compile(r'[)(+-]|\d+')

class Solution:
    def calculate(self, s):
        """
        :type s: str
        :rtype: int
        """
        tokens = LEXER.findall(s)
        tokens.append(')')
        it = iter(tokens)

        def evaluate():
            acc = None
            fn = None

            while True:
                tok = next(it)
                if tok == ')':
                    assert acc is not None and fn is None
                    return acc

                if tok == '(':
                    if fn is None:
                        assert acc is None
                        acc = evaluate()
                    else:
                        assert acc is not None
                        acc = fn(acc, evaluate())
                        fn = None
                elif tok in '+-':
                    assert acc is not None and fn is None
                    fn = operator.add if tok == '+' else operator.sub
                else:
                    arg = int(tok)
                    if fn is None:
                        assert acc is None
                        acc = arg
                    else:
                        assert acc is not None
                        acc = fn(acc, arg)
                        fn = None

        return evaluate()
