#!/usr/bin/perl

use strict;
use warnings;
use 5.010;

my $alice = 0;
my $bob = 0;

my @a = split ' ', <>;
my @b = split ' ', <>;

for (0..2) {
    if ($a[$_] > $b[$_]) {
        ++$alice;
    } elsif ($a[$_] != $b[$_]) {
        ++$bob;
    }
}

say "$alice $bob"
