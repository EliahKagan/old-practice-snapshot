#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);
use List::Util qw(all max);

# Verify that our character set represents lowercase 'a' to 'z' contiguously.
my $offset = ord 'a';
my @alpha = split //ms, 'abcdefghijklmnopqrstuvwxyz';
all { ord $alpha[$_] == $_ + $offset } (0..$#alpha)
    or croak q{'a' to 'z' aren't contiguous};

# Read the heights and the word.
my @heights = split /\s+/msx, <>;
scalar @heights == scalar @alpha or croak 'wrong alphabet length';
chomp(my $word = <>);
my @letters = split //ms, $word;

# Compute and print the area that would be needed to display the word.
my $max_height = max map { $heights[ord() - $offset] } @letters;
my $area = $max_height * scalar @letters;
print "$area\n";
