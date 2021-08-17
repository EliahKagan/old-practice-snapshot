#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);
use List::Util qw(all product);

use constant GRID_SIZE => 20;   # the measure of each side of the grid
use constant LEN => 4;          # strand length

my @grid = map { [split q{ }, <>] } (1..GRID_SIZE);
all { @{$_} == GRID_SIZE } @grid or croak 'wrong row length';

my $best = 0;

for my $i (0  .. GRID_SIZE - 1) {
    for my $j (0 .. GRID_SIZE - LEN) {
        my $cur = product map { $grid[$i]->[$j + $_] } (0 .. LEN - 1);
        if ($best < $cur) { $best = $cur }
    }
}

for my $i (0 .. GRID_SIZE - LEN) {
    for my $j (0 .. GRID_SIZE - 1) {
        my $cur = product map { $grid[$i + $_]->[$j] } (0 .. LEN - 1);
        if ($best < $cur) { $best = $cur }
    }
}

for my $i (0 .. GRID_SIZE - LEN) {
    for my $j (0 .. GRID_SIZE - LEN) {
        my $cur = product map { $grid[$i + $_]->[$j + $_] } (0 .. LEN - 1);
        if ($best < $cur) { $best = $cur }
    }
}

for my $i (0 .. GRID_SIZE - LEN) {
    for my $j (LEN - 1 .. GRID_SIZE - 1) {
        my $cur = product map { $grid[$i + $_]->[$j - $_] } (0 .. LEN - 1);
        if ($best < $cur) { $best = $cur }
    }
}

print "$best\n";
