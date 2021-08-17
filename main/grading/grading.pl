#!/usr/bin/env perl

use strict;
use warnings;
use POSIX qw(round);

sub round_to_nearest {
    my ($quantum, $value) = @_;
    return round($value / $quantum) * $quantum;
}

<>; # don't need n

while (<>) {
    my $rounded = round_to_nearest 5, $_;
    my $adjusted_grade = ($rounded > $_ && $rounded >= 40 ? $rounded : $_);
    printf "%d\n", $adjusted_grade;
}
