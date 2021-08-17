#!/usr/bin/env perl

use strict;
use warnings;
use 5.010; # for the // operator

use Carp qw(croak);
use Readonly;

Readonly my $PRECISION => 6;

my $n = <>;
my @arr = split / /, <>;
scalar @arr == $n or croak 'array has wrong length';

my %signum_counts;
for my $elem (@arr) { ++$signum_counts{$elem <=> 0} }

for my $signum (1, -1, 0) {
    my $count = $signum_counts{$signum} // 0;
    printf "%.*f\n", $PRECISION, $count / $n;
}
