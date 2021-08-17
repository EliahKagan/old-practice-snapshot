#!/usr/bin/env perl

use strict;
use warnings;
use feature qw(say);
use List::Util qw(sum0);
use Math::BigInt;

for my $n (@ARGV) {
    my $factorial = Math::BigInt->new($n)->bfac;
    say sum0(split //ms, $factorial);
}
