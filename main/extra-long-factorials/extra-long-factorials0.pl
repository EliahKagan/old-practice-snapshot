#!/usr/bin/env perl

use strict;
use warnings;
use bigint;
use List::Util qw(reduce);

sub factorial {
    my ($n) = @_;
    return reduce { $a * $b } 1, (2..$n);
}

my $n = <>;
print factorial($n), "\n";
