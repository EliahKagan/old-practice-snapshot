#!/usr/bin/env perl

use strict;
use warnings;
use List::Util qw(reduce);

sub gcd {
    my ($m, $n) = @_;
    return $n == 0 ? $m : gcd($n, $m % $n);
}

sub gcd_list {
    my @nums = @_;
    return reduce { gcd $a, $b } sort { $a <=> $b } @nums;
}

sub read_record {
    return split /\s+/msx, <>;
}

for (1..<>) {
    <>; # don't need n
    print gcd_list(read_record) == 1 ? "YES\n" : "NO\n";
}
