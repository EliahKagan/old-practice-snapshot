#!/usr/bin/env python3

from html.parser import HTMLParser
from sys import stdin

class MyHTMLParser(HTMLParser):
    @staticmethod
    def _print_attrs(attrs):
        for name, value in attrs:
            print('-> {} > {}'.format(name, value))

    def handle_starttag(self, tag, attrs):
        print('Start : ' + tag)
        MyHTMLParser._print_attrs(attrs)

    def handle_startendtag(self, tag, attrs):
        print('Empty : ' + tag)
        MyHTMLParser._print_attrs(attrs)

    def handle_endtag(self, tag):
        print('End   : ' + tag)

parser = MyHTMLParser()
parser.feed(stdin.read())
parser.close()
