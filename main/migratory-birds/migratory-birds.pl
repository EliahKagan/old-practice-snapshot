#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);

my $n = <>;
my @types = split / /ms, <>;
scalar @types == $n or croak 'wrong record length';

my $best_type;
my $best_count = 0;
my %counts;

for my $type (@types) {
    my $count = ++$counts{$type};

    if ($best_count < $count
            || ($best_count == $count && $best_type > $type)) {
        $best_count = $count;
        $best_type = $type;
    }
}

print "$best_type\n";
