#!/usr/bin/env python3

import re

EMAIL = re.compile(r'[A-Za-z0-9_-]+@[A-Za-z0-9]+\..{1,3}')

def fun(s):
    return EMAIL.fullmatch(s)

def filter_mail(emails):
    return list(filter(fun, emails))

if __name__ == '__main__':
    n = int(input())
    emails = []
    for _ in range(n):
        emails.append(input())

filtered_emails = filter_mail(emails)
filtered_emails.sort()
print(filtered_emails)
