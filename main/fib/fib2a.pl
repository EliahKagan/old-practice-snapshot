#!/usr/bin/env perl

use strict;
use warnings;

for my $arg (@ARGV) {
    my $m = 0;
    my $n = 1;
    use bigint;
    ($m, $n) = ($n, $m + $n) while $arg-- > 0;
    print "$m\n";
}
