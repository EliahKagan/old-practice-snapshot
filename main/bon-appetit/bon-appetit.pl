#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);
use List::Util qw(sum);

sub read_record {
    return split / /ms, <>;
}

my ($n, $k) = read_record;
my @c = read_record;
scalar @c == $n or croak 'wrong record length';
my $b_charged = <>;

my $b_actual = (sum(@c) - $c[$k]) / 2;

if ($b_charged == $b_actual) {
    print "Bon Appetit\n";
} else {
    printf "%d\n", $b_charged - $b_actual;
}
