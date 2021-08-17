#!/usr/bin/env perl

use strict;
use warnings;
use List::Util qw(max sum);

<>; # don't need n
my @heights = split / /, <>;

my $max_height = max @heights;
my $freq = sum map { $_ == $max_height } @heights;
print "$freq\n";
