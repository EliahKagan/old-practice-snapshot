#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);

sub read_record {
    return split /\s+/msx, <>;
}

for (1..<>) {
    <> == 2 or croak q{this version only supports n == 2};
    my ($left_green, $left_red) = read_record;
    my ($right_green, $right_red) = read_record;
    my $possible = $left_green == $right_red || $left_red == $right_green;
    print $possible ? "Possible\n" : "Impossible\n";
}
