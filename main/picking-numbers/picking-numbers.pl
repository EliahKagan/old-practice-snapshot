#!/usr/bin/env perl

use strict;
use warnings;
use 5.010;

<>; # don't need n
my %counts;
for my $key (split /\s+/msx, <>) { ++$counts{$key} }

my $best = 0;
for my $key (keys %counts) {
    my $cur = $counts{$key} + ($counts{$key + 1} // 0);
    if ($best < $cur) { $best = $cur }
}

say $best;
