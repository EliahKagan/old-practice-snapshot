#!/usr/bin/env perl

use strict;
use warnings;

<>; # don't need n
my @heights = sort { $a <=> $b } split /\s+/msx, <>;

my $floor = 0;
for my $i (0..$#heights) {
    if ($floor < $heights[$i]) {
        print scalar(@heights) - $i, "\n";
        $floor = $heights[$i];
    }
}
