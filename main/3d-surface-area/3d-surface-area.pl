#!/usr/bin/env perl

use strict;
use warnings;

sub read_record {
    return split /\s+/msx, <>;
}

sub read_row {
    return (0, read_record, 0);
}

my ($height, $width) = read_record;
my @zero_row = (0) x ($width + 2); # OK to use twice as the board never changes
my @board = (\@zero_row, (map { [read_row] } (1..$height)), \@zero_row);

my $area = $height * $width * 2; # top and bottom

for my $i (0..$height) {
    for my $j (0..$width) {
        $area += abs $board[$i]->[$j] - $board[$i]->[$j + 1];
        $area += abs $board[$i]->[$j] - $board[$i + 1]->[$j];
    }
}

print "$area\n";
