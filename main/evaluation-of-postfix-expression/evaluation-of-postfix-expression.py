#!/usr/bin/env python3

import operator

OPERATORS = {'+': operator.add, '-': operator.sub,
             '*': operator.mul, '/': operator.floordiv, '%': operator.mod,
             '&': operator.and_, '|': operator.or_, '^': operator.xor}

def lex(lexeme):
    '''"Lexes" a single one-character lexeme of an arithmetic expression,
    interpreting it as either an operand or operator and converting it to an
    appropriate symbolic token.'''
    try:
        return int(lexeme)
    except:
        return OPERATORS[lexeme]

def rpn_eval(expr):
    '''Evalutes an trivial expression in reverse Polish notation (postfix
    notation). A trivial expression is one where every term is one character
    long, with no whitespace between (e.g., "23+" means the sum of 2 and 3).'''
    stack = []

    for token in map(lex, expr.strip()):
        if type(token) is int:
            stack.append(token)
        else: # we have an operator
            rhs = stack.pop()
            lhs = stack.pop()
            stack.append(token(lhs, rhs))

    # TODO: Make this (and everything else!) raise reasonable ValueError
    #       exceptions instead, if we need to accommodate arbitrary user input.
    assert len(stack) == 1

    return stack.pop()

for _ in range(int(input())):
    print(rpn_eval(input()))
