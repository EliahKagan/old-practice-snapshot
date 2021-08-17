#!/usr/bin/env perl

use strict;
use warnings;

my %f;

while (<>) {
    for my $w (split q{ }) { ++$f{$w} }
}

for my $w (reverse sort { $f{$a} <=> $f{$b} } keys %f) {
    printf "$w $f{$w}\n";
}
