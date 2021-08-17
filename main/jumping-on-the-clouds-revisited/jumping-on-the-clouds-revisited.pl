#!/usr/bin/env perl

use strict;
use warnings;

sub read_record {
    return split /\s+/msx, <>;
}

my ($n, $k) = read_record;
my @c = read_record;

my $jump_cost = 1;
my $thunder_penalty = 2;

my $e = 100;    # starting energy
my $i = 0;      # starting position

do {
    $i = ($i + $k) % $n;
    $e -= $jump_cost + $c[$i] * $thunder_penalty;
} while ($i != 0);

print "$e\n";
