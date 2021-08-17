OPERATORS = {'+': operator.add,
             '-': operator.sub,
             '*': operator.mul,
             '/': lambda arg1, arg2: int(arg1 / arg2)}

class Solution:
    def evalRPN(self, tokens):
        """
        :type tokens: List[str]
        :rtype: int
        """
        stack = []

        for tok in tokens:
            try:
                stack.append(int(tok))
            except ValueError:
                arg2 = stack.pop()
                arg1 = stack.pop()
                stack.append(OPERATORS[tok.strip()](arg1, arg2))

        result, = stack
        return result
