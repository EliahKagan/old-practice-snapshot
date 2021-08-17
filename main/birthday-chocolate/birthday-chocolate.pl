#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);

sub read_record {
    return split / /ms, <>;
}

sub read_values {
    my $len = <>;
    my @values = read_record;
    scalar @values == $len or croak 'wrong record length';
    return @values;
}

sub count_window_sums {
    my ($window_width, $target_sum, @values) = @_;
    if (scalar @values < $window_width) { return 0 }

    my $acc = 0;
    for my $i (0 .. ($window_width - 1)) { $acc += $values[$i] }
    my $count = ($acc == $target_sum ? 1 : 0);

    for my $j ($window_width .. $#values) {
        $acc += $values[$j] - $values[$j - $window_width];
        if ($acc == $target_sum) { ++$count }
    }

    return $count;
}

my @values = read_values;
my ($target_sum, $window_width) = read_record;
print count_window_sums($window_width, $target_sum, @values);
