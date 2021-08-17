#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);

sub read_record {
    return split /\s+/msx, <>;
}

sub is_class_canceled {
    my ($needed, @arrivals) = @_;
    if ($needed <= 0) { return 0 }

    for my $time (@arrivals) {
        if ($time <= 0 && --$needed == 0) { return 0 }
    }

    return 1;
}

for (1..<>) {
    my ($len, $needed) = read_record;
    my @arrivals = read_record;
    scalar @arrivals == $len or croak 'wrong record length';

    print is_class_canceled($needed, @arrivals) ? "YES\n" : "NO\n";
}
