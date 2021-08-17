#!/usr/bin/env perl

use strict;
use warnings;

sub count_running_optima {
    my ($comp, $best, @tail) = @_;
    my $count = 0;

    for my $cur (@tail) {
        if ($comp->($best, $cur)) {
            $best = $cur;
            ++$count;
        }
    }

    return $count;
}

<>; # don't need n
my @s = split / /, <>;

my $count_max = count_running_optima sub { $_[0] < $_[1] }, @s;
my $count_min = count_running_optima sub { $_[0] > $_[1] }, @s;
print "$count_max $count_min\n";
