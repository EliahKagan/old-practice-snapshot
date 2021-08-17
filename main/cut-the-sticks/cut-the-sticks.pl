#!/usr/bin/env perl

use strict;
use warnings;

<>; # don't need n
my @heights = sort { $a <=> $b } split /\s+/msx, <>;

my $remaining = scalar @heights;
my $floor = 0;

for my $height (@heights) {
    if ($floor < $height) {
        print "$remaining\n";
        $floor = $height;
    }

    --$remaining;
}
