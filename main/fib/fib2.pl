#!/usr/bin/env perl

use strict;
use warnings;
use bigint;

for my $arg (@ARGV) {
    my $m = 0;
    my $n = 1;
    ($m, $n) = ($n, $m + $n) while $arg-- > 0;
    print "$m\n";
}
