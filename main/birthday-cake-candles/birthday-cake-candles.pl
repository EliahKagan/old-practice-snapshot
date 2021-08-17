#!/usr/bin/perl

use strict;
use warnings;
use 5.010;

use List::Util qw(max);

<>; # don't need n

my %counts;
++$counts{$_} for split ' ', <>;

my $key = max(keys %counts);
say $counts{$key};
