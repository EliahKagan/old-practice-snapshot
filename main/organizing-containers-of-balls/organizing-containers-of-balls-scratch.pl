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
    my @a = @_;
    return map { sum0 @{ $_ } } @a;
}

my @a = read_matrix;
my ($sum_top, $sum_bot) = get_row_sums @a;

print "$a[0]->[0] $a[0]->[1] $sum_top\n";
print "$a[1]->[0] $a[1]->[1] $sum_bot\n";
