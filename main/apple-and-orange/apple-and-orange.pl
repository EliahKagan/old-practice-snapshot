#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);
use List::Util qw(sum0);

sub read_record {
    return split / /, <>;
}

my ($target_min, $target_max) = read_record;
my ($source_a, $source_b) = read_record;
my ($m, $n) = read_record;
my @displacements_a = read_record;
my @displacements_b = read_record;

scalar @displacements_a == $m or croak 'wrong m';
scalar @displacements_b == $n or croak 'wrong n';

sub hitscan {  # tells if the attack succeeded (the fruit fell on the house)
    my ($source, $displacement) = @_;
    my $destination = $source + $displacement;
    return $target_min <= $destination && $destination <= $target_max;
}

sub compute_damage {  # counts hits
    my ($source, @displacements) = @_;
    return sum0 map { hitscan $source, $_ } @displacements;
}

print compute_damage($source_a, @displacements_a), "\n";
print compute_damage($source_b, @displacements_b), "\n";
