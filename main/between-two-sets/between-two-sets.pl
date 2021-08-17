#!/usr/bin/env perl

use strict;
use warnings;
use List::Util qw(reduce);

sub gcd {
    my ($m, $n) = @_;
    return $n == 0 ? $m : gcd($n, $m % $n);
}

sub lcm {
    my ($m, $n) = @_;
    return int($m / gcd($m, $n)) * $n;
}

sub read_tokens {
    return split / /, <>;
}

sub read_as_bound (&) {
    my $reducer = \&{shift @_};
    return reduce { $reducer->($a, $b) } sort { $a <=> $b } read_tokens;
}

<>; # don't need n, m
my $lower = read_as_bound \&lcm;
my $upper = read_as_bound \&gcd;

my $count = 0;
for (my $multiple = $lower; $multiple <= $upper; $multiple += $lower) {
    if ($upper % $multiple == 0) { ++$count }
}

print "$count\n";
