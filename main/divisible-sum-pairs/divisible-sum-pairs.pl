#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);

sub read_record {
    return split / /ms, <>;
}

my ($n, $k) = read_record;
my @a = read_record;
scalar @a == $n or croak 'wrong record length';

my $count = 0;

for my $i (0 .. ($#a - 1)) {
    for my $j (($i + 1) .. $#a) {
        if (($a[$i] + $a[$j]) % $k == 0) { ++$count }
    }
}

print "$count\n";
