#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);

my $n = <>;
my $acc = 0;

for my $i (1..$n) {
    my @row = split / /, <>;
    scalar @row == $n or croak 'wrong row size';
    $acc += $row[$i - 1] - $row[-$i];
}

print abs $acc, "\n";
