#!/usr/bin/perl

use strict;
use warnings;
use 5.010;

my $acc = 0;

for (1..<>) {
    my @row = split ' ', <>;
    $acc += $row[$_ - 1] - $row[-$_];
}

say abs($acc);
