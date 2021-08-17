#!/usr/bin/perl

use strict;
use warnings;
use Carp qw(croak);

my $n = <>;
my @c = split /\s+/msx, <>;
scalar @c == $n or croak 'wrong record length';
push @c, 1; # put a virtual thundercloud at the end to prevent jumping too far

my $jumps = my $i = 0;

CLOUD:
while ($i != $n - 1) {
    DISTANCE:
    for my $d (2, 1) {
        if (not $c[$i + $d]) {
            $i += $d;
            next CLOUD;
        }
    }

    croak q{can't win};
} continue {
    ++$jumps;
}

print "$jumps\n";
