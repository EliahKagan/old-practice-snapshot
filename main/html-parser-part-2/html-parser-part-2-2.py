#!/usr/bin/env python3

from html.parser import HTMLParser
from sys import stdin

class MyHTMLParser(HTMLParser):
    def handle_data(self, data):
        if data != '\n':
            print('>>> Data')
            print(data)

    def handle_comment(self, data):
        lines = data.split('\n')
        kind = ('Single' if len(lines) == 1 else 'Multi')
        print('>>> %s-line Comment' % kind)
        print(*lines, sep='\n')

stdin.readline()
parser = MyHTMLParser()
parser.feed(stdin.read())
parser.close()
