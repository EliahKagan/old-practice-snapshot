#!/usr/bin/perl

use strict;
use warnings;
use 5.010;

my $m = $ARGV[0] + 0;
my $n = $ARGV[1] + 0;
my $w = length($m * $n) + 1;

for (my $i = 0; $i < $m; ++$i) {
    for (my $j = 0; $j < $n; ++$j) { printf '%*d', $w, $n * $i + $j };
    print "\n";
}
