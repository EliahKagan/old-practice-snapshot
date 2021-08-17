#!/usr/bin/env perl

use strict;
use warnings;

for (1..<>) {
    chomp(my $n = <>);

    my $count = 0;
    for my $ch (split //ms, $n) {
        if ($ch != 0 && $n % $ch == 0) { ++$count }
    }

    print "$count\n";
}
