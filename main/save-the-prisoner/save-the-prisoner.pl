#!/usr/bin/env perl

use strict;
use warnings;

for (1..<>) {
    my ($n, $m, $s) = split /\s+/msx, <>;
    print(($s + $m - 2) % $n + 1, "\n");
}
