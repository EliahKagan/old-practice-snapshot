#!/usr/bin/env perl

use strict;
use warnings;
use bigint;

for my $arg (@ARGV) {
    my $acc = 1;
    $acc *= $_ for (2..$arg);
    print "$acc\n";
}
