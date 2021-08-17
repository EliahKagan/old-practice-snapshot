#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);

my $len = <>;
my @colors = split / /ms, <>;
scalar @colors == $len or croak 'wrong record length';

my %counts;
for my $color (@colors) { ++$counts{$color} }

my $npairs = 0;
for my $count (values %counts) { $npairs += int($count / 2) }
print "$npairs\n";
