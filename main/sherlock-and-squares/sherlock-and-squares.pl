#!/usr/bin/env perl

use strict;
use warnings;
use List::Util qw(max);
use POSIX qw(ceil floor);

for (1..<>) {
    my ($low, $high) = split /\s+/msx, <>;

    my $low_sqrt = ceil sqrt $low;
    my $high_sqrt = floor sqrt $high;
    print max(0, $high_sqrt - $low_sqrt + 1), "\n";
}
