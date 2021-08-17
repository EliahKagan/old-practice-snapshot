#!/usr/bin/env perl

use strict;
use warnings;

my $sum = my $cur = 2;
for (1 .. (<> - 1)) { $sum += ($cur = int($cur * 3 / 2)) }
print "$sum\n";
