#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);

my $len = <>;
my @arr = split / /, <>;
scalar @arr == $len or croak 'array has wrong length';

my $ps = 0;
my $ns = 0;
my $zs = 0;

for my $elem (@arr) {
    if ($elem > 0) {
        ++$ps;
    } elsif ($elem < 0) {
        ++$ns;
    } else {
        ++$zs;
    }
}

for my $count ($ps, $ns, $zs) { printf "%.6f\n", $count / $len }
