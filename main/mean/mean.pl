#!/usr/bin/perl

use strict;
use warnings;
use 5.010;

sub mean {
    my $acc = 0;
    $acc += $_ for @_;
    $acc / @_
}

say mean(@ARGV);
