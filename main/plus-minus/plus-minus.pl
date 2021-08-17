#!/usr/bin/perl

use strict;
use warnings;

my $n = <>;
my $ps = my $ns = my $zs = 0;

for (split ' ', <>) {
    if ($_ > 0) {
        ++$ps;
    } elsif ($_ != 0) {
        ++$ns;
    } else {
        ++$zs;
    }
}

printf "%.6f\n", $_ / $n for ($ps, $ns, $zs);
