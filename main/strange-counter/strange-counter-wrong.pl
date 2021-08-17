#!/usr/bin/env perl

use strict;
use warnings;
use POSIX qw(ceil);

sub min_time_from_cycle {
    my ($cycle) = @_;
    return ($cycle - 1) * $cycle / 2 + 1;
}

sub cycle_from_time {
    my ($time) = @_;
    return ceil((sqrt($time * 24 + 9) - 3) / 6);
}

sub range_of_cycle {
    my ($cycle) = @_;
    return $cycle * 3;
}

my $time = <>;
my $cycle = cycle_from_time $time;
my $min_time = min_time_from_cycle $cycle;
print range_of_cycle($cycle) - ($time - $min_time), "\n";
