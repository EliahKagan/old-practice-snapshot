#!/usr/bin/env perl

use strict;
use warnings;
use List::Util qw(max sum0);

<>; # don't need n
my %counts;
for my $key (split /\s+/msx, <>) { ++$counts{$key} }

print sum0(values %counts) - max(values %counts), "\n";
