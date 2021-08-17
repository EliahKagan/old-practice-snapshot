#!/usr/bin/env perl

use strict;
use warnings;

sub read_record {
    <>; # don't need n or m
    return split /\s+/msx, <>;
}

sub without_consecutive_dupes {
    my @values = @_;
    @values or return [];

    my @ret = (my $prev = shift @values);

    for my $cur (@values) {
        if ($prev != $cur) {
            $prev = $cur;
            push @ret, $cur;
        }
    }

    return @ret;
}

my @board = without_consecutive_dupes read_record;
my $rank = scalar @board; # zero-based

for my $score (read_record) {
    while ($rank != 0 && $board[$rank - 1] <= $score) { --$rank }
    print $rank + 1, "\n"; # so that it is zero-based
}
