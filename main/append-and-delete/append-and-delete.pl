#!/usr/bin/env perl

use strict;
use warnings;
use List::Util qw(min);

sub letters {
    my ($word) = @_;
    chomp $word;
    return split //ms, $word;
}

sub prefix_length {
    my ($s, $t) = @_;

    my @a = letters $s;
    my @b = letters $t;
    my $istop = min scalar(@a), scalar(@b);

    my $i = 0;
    while ($i != $istop && $a[$i] eq $b[$i]) { ++$i }
    return $i;
}

sub can_convert_to {
    my ($s, $t, $k) = @_;

    my $comb = length($s) + length($t);
    my $same = prefix_length $s, $t;
    my $diff = $comb - $same * 2;

    return $k >= $diff && ($k > $comb || $k % 2 == $diff % 2);
}

my $s = <>;
my $t = <>;
my $k = <>;

print can_convert_to($s, $t, $k) ? "Yes\n" : "No\n";
