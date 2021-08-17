#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);

for (1..<>) {
    <>; # don't need n
    my ($max, @tail) = split /\s+/msx, <>;
    defined $max or croak 'no data';
    my $steps = 1;

    for my $cur (@tail) {
        if ($max < $cur) {
            $max = $cur;
            ++$steps;
        }
    }

    print $steps % 2 == 0 ? "ANDY\n" : "BOB\n";
}
