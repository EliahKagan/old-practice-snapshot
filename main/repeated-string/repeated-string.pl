#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);

# Get an array whose $k-indexed element is the number of ($key)s encountered
# in the first $k characters of $s.
sub get_counts_of {
    my ($key, $s) = @_;

    my @counts;
    push @counts, my $count = 0;
    for my $ch (split //msx, $s) { push @counts, $count += ($ch eq $key) }

    return @counts;
}

chomp(my $s = <>);
my @counts = get_counts_of 'a', $s;
my $len = length $s;
$#counts == $len or croak 'Internal error: counts array has wrong max index';

my $n = <>;
print $counts[$len] * int($n / $len) + $counts[$n % $len], "\n";
