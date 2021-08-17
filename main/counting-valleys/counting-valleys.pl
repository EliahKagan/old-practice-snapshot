#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);

sub count_valleys {
    my ($trek) = @_;

    my $level = 0;
    my $count = 0;

    for my $step (split //ms, $trek) {
        if ($step eq 'U') {
            if (++$level == 0) { ++$count }
        } elsif ($step eq 'D') {
            --$level;
        } else {
            croak 'unrecognized step';
        }
    }

    return $count;
}

my $len = <>;
chomp(my $trek = <>);
length $trek == $len or croak 'wrong number of steps';

print count_valleys($trek), "\n";
