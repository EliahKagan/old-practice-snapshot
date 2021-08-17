#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);

sub read_record {
    return split /\s+/msx, <>;
}

my ($n, $k, $q) = read_record;
my @a = read_record;
scalar @a == $n or croak 'wrong record length';

for (1..$q) { print "$a[(<> - $k) % $n]\n" }
