#!/usr/bin/env perl

use strict;
use warnings;
use 5.010;
use POSIX qw(ceil);

sub log2 {
    my ($x) = @_;
    state $denom = log 2;
    return (log $x) / $denom;
}

my $t = <>;
my $group = ceil(log2($t / 3 + 1)) - 1; # group number, using 0-based indexing
my $grange = 3 * 2**$group;             # number of items in the current group
my $offset = $grange - 3;               # highest number in previous group
my $pos =  $t - $offset;                # position in its own group
say $grange - $pos + 1
