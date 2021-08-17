#!/usr/bin/env python3

from html.parser import HTMLParser
from sys import stdin

class MyHTMLParser(HTMLParser):
    @staticmethod
    def _print(tag, attrs):
        print(tag)
        for name, value in attrs:
            print('-> {} > {}'.format(name, value))

    def handle_starttag(self, tag, attrs):
        MyHTMLParser._print(tag, attrs)

    def handle_startendtag(self, tag, attrs):
        MyHTMLParser._print(tag, attrs)

parser = MyHTMLParser()
parser.feed(''.join(stdin.readlines()))
parser.close()
