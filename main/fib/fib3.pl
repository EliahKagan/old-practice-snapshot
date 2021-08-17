#!/usr/bin/env perl

use strict;
use warnings;
use bigint;

for my $arg (@ARGV) {
    my $m = 0;
    my $n = 1;

    while ($arg -- > 0) {
        ($m, $n) = ($n, $m + $n);
        print {*STDERR} "($m, $n)\n";
    }

    print "$m\n";
}
