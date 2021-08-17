#!/usr/bin/env perl

use strict;
use warnings;
use experimental qw(lexical_subs);
use feature qw(say);

sub count_beautiful_days {
    my ($i, $j, $k) = @_;

    my sub is_beautiful {
        my ($x) = @_;
        return ($x - scalar reverse $x) % $k == 0;
    }

    my $count = 0;
    for my $x ($i..$j) {
        if (is_beautiful $x) { ++$count }
    }

    return $count;
}

say count_beautiful_days(split /\s+/msx, <>);
