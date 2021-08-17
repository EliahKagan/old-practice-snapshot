#!/usr/bin/env perl

use strict;
use warnings;

for (1..<>) {
    <>; # don't need n
    my @values = split /\s+/msx, <>;
    my @indices = reverse sort { $values[$a] <=> $values[$b] } (0..$#values);

    my $cut = scalar @values;
    my $steps = 0;

    for my $idx (@indices) {
        if ($idx < $cut) {
            ++$steps;
            $cut = $idx;
            if ($cut == 0) { last } # a simple optimization
        }
    }

    print $steps % 2 == 0 ? "ANDY\n" : "BOB\n";
}
