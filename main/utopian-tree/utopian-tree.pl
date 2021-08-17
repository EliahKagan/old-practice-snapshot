#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);

use constant SPRING => 0;
use constant SUMMER => 1;

sub height_after_growth {
    (my $cycles = shift) >= 0 or croak 'cycles must be nonnegative';
    (my $height = shift // 1) > 0 or croak 'height must be positive';
    my $season = shift // SPRING;

    if ($cycles == 0) { return $height }

    if ($season == SPRING) {
        return height_after_growth($cycles - 1, $height * 2, SUMMER);
    } elsif ($season == SUMMER) {
        return height_after_growth($cycles - 1, $height + 1, SPRING);
    } else {
        croak 'unrecognized season';
    }
}

for (1..<>) {
    my $cycles = <>;
    print height_after_growth($cycles), "\n";
}
