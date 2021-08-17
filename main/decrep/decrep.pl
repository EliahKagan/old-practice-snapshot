#!/usr/bin/env perl
# https://codereview.stackexchange.com/q/3714, but in Perl 5 instead of C++03,
# and with the added requirement to print output in perfectly aligned columns.

use strict;
use warnings;
use 5.008; # for stable sort

use locale;
use sort 'stable';
use List::Util qw(max);

sub max_width {
    my @items = @_;
    return max map {length} @items;
}

my %counts;

while (<>) {
    s/\A\s+//msx;
    s/\s+\z//msx;
    if (length != 0) { ++$counts{$_} }
}

my @keys = keys %counts;
my $keys_width = max_width @keys;
my $counts_width = max_width values %counts;

# Sort keys decreasingly by count, breaking ties lexicographically.
for my $key (sort { -($counts{$a} <=> $counts{$b}) || $a cmp $b } @keys) {
    printf "%*s  %*d\n", -$keys_width, $key, $counts_width, $counts{$key};
}
