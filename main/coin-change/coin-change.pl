#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);

sub read_record {
    return split /\s+/msx, <>;
}

my ($total, $len) = read_record;
my @coins = read_record;
$len == scalar @coins or croak 'wrong record length';

my %memo; # "$index $subtotal" => $count

sub count_ways {
    my ($index, $subtotal) = @_;

    if ($subtotal == 0) { return 1 }
    if ($index == $len) { return 0 }

    my $key = "$index $subtotal";
    my $count = $memo{$key};

    if (!defined $count) {
        my $coin = $coins[$index];
        my $next_index = $index + 1;

        $count = 0;
        while ($subtotal >= 0) {
            $count += count_ways($next_index, $subtotal);
            $subtotal -= $coin;
        }

        $memo{$key} = $count;
    }

    return $count;
}

print count_ways(0, $total), "\n";
