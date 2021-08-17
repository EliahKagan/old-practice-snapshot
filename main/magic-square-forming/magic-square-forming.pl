#!/usr/bin/env perl

use strict;
use warnings;
use 5.010;
use English qw(-no_match_vars);

# All eight 3x3 magic squares. See:
# https://mindyourdecisions.com/blog/2015/11/08/how-many-3x3-magic-squares-are-there-sunday-puzzle/
my @squares = ([8, 1, 6, 3, 5, 7, 4, 9, 2],
               [6, 1, 8, 7, 5, 3, 2, 9, 4],
               [4, 9, 2, 3, 5, 7, 8, 1, 6],
               [2, 9, 4, 7, 5, 3, 6, 1, 8],
               [8, 3, 4, 1, 5, 9, 6, 7, 2],
               [4, 3, 8, 9, 5, 1, 2, 7, 6],
               [6, 7, 2, 1, 5, 9, 8, 3, 4],
               [2, 7, 6, 9, 5, 1, 4, 3, 8],);

local $INPUT_RECORD_SEPARATOR = undef; # slurp
my @a = split /\s+/msx, <>;
my $best;

for my $s (@squares) {
    my $cur = 0;
    for my $i (0 .. $#{$s}) { $cur += abs $a[$i] - $s->[$i] }
    if (($best // $cur) >= $cur) { $best = $cur }
}

say $best;
