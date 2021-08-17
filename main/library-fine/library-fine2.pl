#!/usr/bin/env perl

use strict;
use warnings;

sub read_record {
    return split /\s+/msx, <>;
}

my ($day_returned, $month_returned, $year_returned) = read_record;
my ($day_due, $month_due, $year_due) = read_record;

my $fine = $year_returned < $year_due   ? 0
         : $year_returned > $year_due   ? 10_000
         : $month_returned < $month_due ? 0
         : $month_returned > $month_due ? 500 * ($month_returned - $month_due)
         : $day_returned <= $day_due    ? 0
         :                                15 * ($day_returned - $day_due);

print "$fine\n";
