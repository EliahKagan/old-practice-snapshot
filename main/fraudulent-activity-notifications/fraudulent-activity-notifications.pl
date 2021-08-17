#!/usr/bin/env perl

use strict;
use warnings;
use feature qw(say);
use experimental qw(lexical_subs);
use Carp qw(croak);
use List::Util qw(min);

use constant MAX_VALUE => 200;

sub read_record {
    return split /\s+/msx, <>;
}

my ($total_count, $window_size) = read_record;
my @values = read_record;
$total_count == scalar @values
    or croak q{total count doesn't match record length};
(0 < $window_size && $window_size <= $total_count)
    or croak q{unusable window size};

my $min_value = min @values;
0 <= $min_value or croak 'negative values are not allowed';

my @counts = (0) x (MAX_VALUE + 1);
for my $day (0 .. $window_size - 1) { ++$counts[$values[$day]] }

my $left_medial_count = int(($window_size + 1) / 2);
my $right_medial_count = int($window_size / 2) + 1;

(0 < $left_medial_count && $left_medial_count <= $right_medial_count
                        && $right_medial_count <= $left_medial_count + 1)
    or croak 'Internal error: computed medial counts are somehow wrong';

my sub compute_doubled_median {
    my $running_count = 0;
    my $value = $min_value - 1; # becomes the 1st value after initial increment

    my sub count_to {
        my ($target) = @_;

        while ($running_count < $target) {
            $running_count += $counts[++$value];
        }

        return $value;
    }

    my $left_medial_value = count_to $left_medial_count;
    my $right_medial_value = count_to $right_medial_count;
    return $left_medial_value + $right_medial_value;
}

my $notifications = 0;
for my $day ($window_size .. $total_count - 1) {
    # check today's value against the median _before_ sliding the window right
    if ($values[$day] >= compute_doubled_median) { ++$notifications }

    # update counts for the effect of sliding the window to the right
    ++$counts[$values[$day]];
    --$counts[$values[$day - $window_size]];
}

say $notifications;
