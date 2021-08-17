#!/usr/bin/env perl

use strict;
use warnings;
use bigint;

@ARGV == 1 or die "$0: error: need exactly one argument\n";
my ($len) = @ARGV;

my @fib = (0, 1);
for my $i (2 .. $len - 1) {
    $fib[$i] = $fib[$i - 2] + $fib[$i - 1];
}

print "@fib[0 .. $len - 1]\n";
