#!/usr/bin/env perl

use strict;
use warnings;

sub write_special_date {
    my ($year, $is_leap_year) = @_;
    return printf "1%s.09.%d\n", ($is_leap_year ? '2' : '3'), $year;
}

my $y = <>;

if ($y < 1918) {
    write_special_date($y, $y % 4 == 0);
} elsif ($y == 1918) {
    print "26.09.1918\n";
} else {
    write_special_date($y, $y % 400 == 0 || ($y % 4 == 0 && $y % 100 != 0));
}
