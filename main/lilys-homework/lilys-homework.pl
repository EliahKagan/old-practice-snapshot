#!/usr/bin/env perl

use strict;
use warnings;
use feature qw(say);
use List::Util qw(min);

use constant VISITED => -1;

sub normalize_to_permutation {
    my ($values) = @_;

    my @permutation = sort { $values->[$a] <=> $values->[$b] }
                           (0..$#{$values});
    return @permutation;
}

# Traverses the cycle of the permutation that begins at the index start,
# marking each element visited and returning the number of positions traversed
# (always at least 1).
sub traverse_and_mark_cycle {
    my ($permutation, $start) = @_;

    my $i = $start;
    my $cycle_length = 1;

    while (1) {
        # advance to the next value in the cycle
        ($permutation->[$i], $i) = (VISITED, $permutation->[$i]);

        if ($i == $start) { return $cycle_length }
        ++$cycle_length;
    }
}

sub compute_min_swaps {
    my ($values) = @_;

    my @permutation = normalize_to_permutation $values;
    my $swaps = 0;

    for my $i (0..$#permutation) {
        if ($permutation[$i] != VISITED) {
            $swaps += traverse_and_mark_cycle(\@permutation, $i) - 1;
        }
    }

    return $swaps;
}

<>; # don't need n
my @values = split /\s+/msx, <>;
say min(compute_min_swaps(\@values), compute_min_swaps([reverse @values]));
