#!/usr/bin/env perl

use strict;
use warnings;
use feature qw(say);
use experimental qw(signatures);
use Carp qw(croak);

package DisjointSets {
    # Performs $element_count makeset operations.
    sub new($class, $element_count) {
        my $self = [(-1) x ($element_count + 1)]; # +1 for 1-based indexing
        bless $self, $class;
    }

    # Gets the cardinality of the set containing $elem.
    sub size($self, $elem) {
        $elem = $self->_find_set($elem);
        -$self->[$elem]; # Size is stored negative. (Nonnegatives are parents.)
    }

    # Unites the sets containing $elem1 and $elem2.
    sub union($self, $elem1, $elem2) {
        # Find the ancestors and stop if they are already the same.
        $elem1 = $self->_find_set($elem1);
        $elem2 = $self->_find_set($elem2);
        return 1 if ($elem1 == $elem2);

        # Union by size.
        if ($self->[$elem2] < $self->[$elem1]) {
            # Set 2 is bigger (more negative) than set 1. Make it the parent.
            $self->_join($elem2, $elem1);
        } else {
            # Set 1 is at least as big as set 2, so make it the parent.
            $self->_join($elem1, $elem2);
        }

        1;
    }

    # Finds the representative element of the set containing $elem.
    sub _find_set($self, $elem) {
        # Find the ancestor.
        my $leader = $elem;
        while ($self->[$leader] >= 0) {
            $leader = $self->[$leader];
        }

        # Compress the path.
        while ($elem != $leader) {
            ($self->[$elem], $elem) = ($leader, $self->[$elem]);
        }

        $leader;
    }

    # Joins the set represented by $child to the set represented by $parent.
    sub _join($self, $parent, $child) {
        $self->[$parent] += $self->[$child];
        $self->[$child] = $parent;
    }
}

sub run() {
    my ($vertex_count, $query_count) = split /\s+/, <<>>;
    my $sets = DisjointSets->new($vertex_count);

    for (1..$query_count) {
        my @tokens = split /\s+/, <<>>;
        my $opcode = shift @tokens;

        if ($opcode eq 'M') {
            my ($u, $v) = @tokens;
            $sets->union($u, $v);
        } elsif ($opcode eq 'Q') {
            my ($u) = @tokens;
            say $sets->size($u);
        } else {
            croak 'unrecognized query type';
        }
    }

    1;
}

run();
