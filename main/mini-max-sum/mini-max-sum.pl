#!/usr/bin/env perl

use strict;
use warnings;
use bigint;
use List::Util qw(sum);

my @tok = split / /, <>;
my @arr = sort { $a <=> $b } @tok;
my $sum = sum @arr;
printf "%d %d\n", $sum - $arr[-1], $sum - $arr[0];
