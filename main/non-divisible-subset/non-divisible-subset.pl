#!/usr/bin/env perl

use strict;
use warnings;
use List::Util qw(max);

sub read_record {
    return split /\s+/msx, <>;
}

my (undef, $k) = read_record; # don't need n
my @bins = (0) * $k;
for my $elem (read_record) { ++$bins[$elem % $k] }

my $acc = 0;

my $i = 1;
my $j = $#bins;
while ($i < $j) { $acc += max $bins[$i++], $bins[$j--] }
if ($i == $j && $bins[$i] != 0 ) { ++$acc }
if ($bins[0] != 0) { ++$acc }

print "$acc\n";
