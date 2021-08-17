#!/usr/bin/env perl
# This is the fast, simple, smart algorithm, by looking ahead.

use strict;
use warnings;
use Carp qw(croak);
use List::Util qw(max);

sub read_record {
    return split /\s+/msx, <>;
}

my ($len, $reach) = read_record;
my @heights = read_record;
scalar @heights == $len or croak 'wrong record length';

print max(max(@heights) - $reach, 0), "\n";
