#!/usr/bin/env perl

use strict;
use warnings;
use feature qw(say);

sub read_record {
    return split /\s+/msx, <>;
}

my ($day_returned, $month_returned, $year_returned) = read_record;
my ($day_due, $month_due, $year_due) = read_record;

if ($year_returned < $year_due) {
    say 0;
} elsif ($year_returned > $year_due) {
    say 10_000;
} elsif ($month_returned < $month_due) {
    say 0;
} elsif ($month_returned > $month_due) {
    say 500 * ($month_returned - $month_due);
} elsif ($day_returned <= $day_due) {
    say 0;
} else {
    say 15 * ($day_returned - $day_due);
}
