#!/usr/bin/env perl

use strict;
use warnings;

my $best = -1;          # the most topics any one team knows
my $best_teams = 0;     # count of teams that know that many

<>; # don't need n, m
chomp(my @a = <>);

for my $i (0 .. $#a - 1) {
    for my $j ($i + 1 .. $#a) {
        my $cur = ($a[$i] | $a[$j]) =~ tr/1//;

        if ($best < $cur) {
            $best = $cur;
            $best_teams = 1;
        } elsif ($best == $cur) {
            ++$best_teams;
        }
    }
}

print "$best\n$best_teams\n";
