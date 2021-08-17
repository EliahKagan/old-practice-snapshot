#!/usr/bin/env python3

from html.parser import HTMLParser

class MyHTMLParser(HTMLParser):
    def handle_data(self, data):
        if data != '\n':
            print('>>> Data')
            print(data)

    def handle_comment(self, data):
        lines = data.split('\n')

        if len(lines) == 1:
            print('>>> Single-line Comment')
        else:
            print('>>> Multi-line Comment')

        for line in lines:
            print(line)

def read_document():
    def helper():
        for _ in range(int(input())):
            yield input().rstrip()
            yield '\n'

    return ''.join(helper())

parser = MyHTMLParser()
parser.feed(read_document())
parser.close()
