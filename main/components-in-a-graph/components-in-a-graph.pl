#!/usr/bin/env perl

use strict;
use warnings;
use feature qw(lexical_subs);
use experimental qw(signatures);
use List::Util qw(min max);

package DisjointSets {
    # Performs $element_count makeset operations.
    sub new($class, $element_count) {
        my $self = { # +1 for 1-based indexing
            parents => [0..$element_count],
            sizes => [(1) x ($element_count + 1)]
        };

        bless $self, $class;
    }

    # Calls a subroutine repeatedly, to process each component size.
    sub each_component_size($self, $code) {
        for my $elem (1..$#{$self->{parents}}) {
            if ($self->{parents}[$elem] == $elem) {
                $code->($self->{sizes}[$elem]);
            }
        }

        1;
    }

    # Unites the sets containing $elem1 and $elem2.
    sub union($self, $elem1, $elem2) {
        # Find the ancestors and stop if they are already the same.
        $elem1 = $self->_find_set($elem1);
        $elem2 = $self->_find_set($elem2);
        return 1 if $elem1 == $elem2;

        # Union by size.
        if ($self->{sizes}[$elem1] < $self->{sizes}[$elem2]) {
            $self->_join($elem2, $elem1);
        } else {
            $self->_join($elem1, $elem2);
        }

        1;
    }

    # Finds the representative element of the set containing $elem.
    sub _find_set($self, $elem) {
        # Find the ancestor.
        my $leader = $elem;
        while ($leader != $self->{parents}[$leader]) {
            $leader = $self->{parents}[$leader];
        }

        # Compress the path.
        while ($elem != $leader) {
            ($self->{parents}[$elem], $elem) =
                    ($leader, $self->{parents}[$elem]);
        }

        $leader;
    }

    # Joins the set represented by $child to the set represented by $parent.
    sub _join($self, $parent, $child) {
        $self->{parents}[$child] = $parent;
        $self->{sizes}[$parent] += $self->{sizes}[$child];
        1;
    }
}

sub min_max_nonsingleton_sizes($sets) {
    my $min = '+inf';
    my $max = '-inf';

    $sets->each_component_size(sub($size) {
        return if $size == 1;
        $min = min($min, $size);
        $max = max($max, $size);
    });

    ($min, $max);
}

sub run {
    my $n = <<>>;
    my $sets = DisjointSets->new($n * 2);

    for (1..$n) {
        my ($u, $v) = split /\s+/, <<>>;
        $sets->union($u, $v);
    }

    my ($min, $max) = min_max_nonsingleton_sizes($sets);
    print "$min $max\n";
}

run();
