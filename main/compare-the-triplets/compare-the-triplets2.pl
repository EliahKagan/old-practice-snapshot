#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);

my @a = split / /, <>;
my @b = split / /, <>;
scalar @a == scalar @b or croak 'unequal array lengths';

my $alice = 0;
my $bob = 0;

for my $i (0..$#a) {
    if ($a[$i] > $b[$i]) {
        ++$alice;
    } elsif ($a[$i] < $b[$i]) {
        ++$bob;
    }
}

print "$alice $bob\n";
