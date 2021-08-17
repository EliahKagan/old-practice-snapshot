#!/usr/bin/env perl

use strict;
use warnings;

sub read_record {
    return split / /ms, <>;
}

my ($cap) = read_record; # need s as $cap, but don't need n, m
my @kbds = read_record;
my @usbs = read_record;

my $best = -1;

for my $kbd (@kbds) {
    for my $usb (@usbs) {
        my $cur = $kbd + $usb;
        if ($best < $cur && $cur <= $cap) { $best = $cur }
    }
}

print $best, "\n";
