#!/usr/bin/env perl

use strict;
use warnings;
use List::Util qw(min);

sub read_record {
    return split /\s+/msx, <>;
}

for (1..<>) {
    my ($black, $white) = read_record;
    my ($black_cost, $white_cost, $conv_fee) = read_record;
    my $total_black_cost = $black * min $black_cost, $white_cost + $conv_fee;
    my $total_white_cost = $white * min $white_cost, $black_cost + $conv_fee;
    print $total_black_cost + $total_white_cost, "\n";
}
