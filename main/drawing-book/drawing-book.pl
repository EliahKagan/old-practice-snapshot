#!/usr/bin/env perl

use strict;
use warnings;
use List::Util qw(min);

sub read_state {
    return int <> / 2;
}

my $last = read_state;
my $cur = read_state;

print min($cur, $last - $cur), "\n";
