#!/usr/bin/env perl

use strict;
use warnings;

local $| = 1;

OWL:
for my $owl (qw(Snowy Barn Short-eared)) {
    GAME:
    for my $game (qw(Chess Checkers Monopoly Scrabble)) {
        print "$owl owl $game!\n> ";
        my $command = <>;
        eval $command;
        print "You and the $owl owl have completed a game of $game.\n";
    } continue {
        print "The $owl owl is done playing $game.\n";
    }
} continue {
    print "The $owl owl has flown away.\n";
}
