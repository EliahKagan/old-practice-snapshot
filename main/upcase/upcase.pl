#!/usr/bin/perl

while (<>) {
    s/(.)/\U$1/g;
    print;
}
