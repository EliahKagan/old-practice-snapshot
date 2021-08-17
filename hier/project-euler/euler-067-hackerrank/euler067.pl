#!/usr/bin/env perl

use strict;
use warnings;
use List::Util qw(max);

sub read_record {
    return split /\s+/msx, <>;
}

for (1..<>) {
    my @grid = map { [read_record] } (1..<>);

    for my $i (1..$#grid) {
        # accumulate the only available "choices" into the two edge cells
        for my $j (0, -1) { $grid[$i]->[$j] += $grid[$i - 1]->[$j] }

        # accumulate the best of two real choices into all non-edge cells
        for my $j (1 .. $#{$grid[$i]} - 1) {
            $grid[$i]->[$j] += max($grid[$i - 1]->[$j - 1],
                                   $grid[$i - 1]->[$j]);
        }
    }

    print max(@{$grid[-1]}), "\n";
}
