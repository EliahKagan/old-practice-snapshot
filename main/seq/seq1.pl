#!/usr/bin/perl

use strict;
use warnings;
use 5.010;

use Switch;

sub range_is_good {
    my ($first, $last, $step) = @_;

    return $first == $last if $step == 0;
    return $first <= $last if $step > 0;
    return $first >= $last if $step < 0;

    die 'invalid step';
}

sub get_range {
    my ($first, $last, $step);

    switch (scalar(@_)) {
        case 0      { die 'too few arguments' }
        case 1      { ($first, $last) = (0, $_[0]) }
        case [2, 3] { ($first, $last, $step) = @_}
        else        { die 'to many arguments' }
    }

    $step = ($first > $last ? -1 : 1) unless defined $step;
    die 'no such sequence' unless range_is_good($first, $last, $step);
    return ($first, $last, $step);
}

sub is_between {
    my ($value, $first, $last) = @_;

    return $first <= $value && $value <= $last if $first <= $last;
    return $first >= $value && $value >= $last if $first > $last;

    die 'invalid range';
}

my ($first, $last, $step) = get_range(@ARGV);

my $delim = '';
for (my $value = $first; is_between($value, $first, $last); $value += $step) {
    print $delim, $value;
    $delim = ' ';
}
print "\n";
