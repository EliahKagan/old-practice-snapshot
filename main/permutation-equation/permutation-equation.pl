#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);

sub inverse {
    my ($p) = @_;

    my @q;
    my $n = $#q = $#{$p};
    for my $i (0..$n) { $q[$p->[$i]] = $i }

    return @q;
}

sub compose {
    my ($p, $q) = @_;

    my $n = $#{$q};
    $#{$p} == $n or croak 'mismatched permutation lengths';

    my @r;
    $#r = $n;
    for my $i (0..$n) { $r[$i] = $q->[$p->[$i]] }

    return @r;
}

sub read_record {
    return split /\s+/msx, <>;
}

my $n = <>;
my @p = (0, read_record);
$#p == $n or croak 'wrong record length';

my @q = inverse \@p;
my @r = compose \@q, \@q;
for my $i (1..$n) { print "$r[$i]\n" }
