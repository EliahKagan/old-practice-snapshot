#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);
use List::Util qw(sum0);

sub read_row {
    my ($n) = @_;
    my @row = split /\s+/msx, <>;
    scalar @row == $n or croak 'wrong row size';
    return \@row;
}

sub read_matrix {
    my $n = <>;
    return map { read_row $n } (1..$n);
}

sub get_row_sums {
    my $rows = \@_;
    return map { sum0 @{$_} } @{$rows};
}

sub get_col_sums {
    my $rows = \@_;
    my @sums;

    for my $i (0..$#{$rows}) {
        push @sums, sum0 map { $_->[$i] } @{$rows};
    }

    return @sums;
}

sub equals { # compare same-length arrays for numeric equality
    my ($lhs, $rhs) = @_;
    $#{$lhs} == $#{$rhs} or croak 'the lists are not the same size';

    for my $i (0..$#{$lhs}) {
        if ($lhs->[$i] != $rhs->[$i]) { return 0 }
    }

    return 1;
}

for (1..<>) {
    my @a = read_matrix;

    # We need the bag of container sizes (number of balls in each container)
    # to be equal to the bag of color counts (number of balls of each color).
    my @container_sizes = sort { $a <=> $b } get_row_sums @a;
    my @color_counts = sort { $a <=> $b } get_col_sums @a;
    my $possible = equals \@container_sizes, \@color_counts;

    print $possible ? "Possible\n" : "Impossible\n";
}
