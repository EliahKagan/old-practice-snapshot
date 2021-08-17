#!/usr/bin/env python3

from html.parser import HTMLParser
from sys import stdin

class MyHTMLParser(HTMLParser):
    def handle_starttag(self, tag, attrs):
        print(tag)
        for name, value in attrs:
            print('-> {} > {}'.format(name, value))

parser = MyHTMLParser()
parser.feed(stdin.read())
parser.close()
