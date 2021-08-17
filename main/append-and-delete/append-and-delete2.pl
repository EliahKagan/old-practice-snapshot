#!/usr/bin/env perl

use strict;
use warnings;
use List::Util qw(min);

sub read_word {
    chomp(my $word = <>);
    return $word;
}

sub letters {
    my ($word) = @_;
    return split //ms, $word;
}

sub prefix_length {
    my ($s, $t) = @_;

    my $istop = min length($s), length($t);

    my $i = 0;
    while ($i != $istop && substr($s, $i, 1) eq substr($t, $i, 1)) { ++$i }
    return $i;
}

sub can_convert_to {
    my ($s, $t, $k) = @_;

    my $comb = length($s) + length($t);
    my $same = prefix_length $s, $t;
    my $diff = $comb - $same * 2;

    return $k >= $diff && ($k > $comb || $k % 2 == $diff % 2);
}

my $s = read_word;
my $t = read_word;
my $k = <>;

print can_convert_to($s, $t, $k) ? "Yes\n" : "No\n";
