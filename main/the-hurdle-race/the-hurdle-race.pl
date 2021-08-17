#!/usr/bin/env perl
# This is the naive algorithm, by playing the game.

use strict;
use warnings;
use Carp qw(croak);

sub read_record {
    return split /\s+/msx, <>;
}

my ($len, $reach) = read_record;
my @heights = read_record;
scalar @heights == $len or croak 'wrong record length';

my $boosts = 0;

for my $height (@heights) {
    if ($reach < $height) {
        $boosts += $height - $reach;
        $reach = $height;
    }
}

print "$boosts\n";
