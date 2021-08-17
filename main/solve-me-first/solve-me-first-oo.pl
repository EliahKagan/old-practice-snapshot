#!/usr/bin/env perl

use strict;
use warnings;
use feature qw(say);

package Adder {
    sub new {
        my ($class, $x) = @_;
        my $self = {x => $x};
        bless $self, $class;
    }

    sub plus {
        my ($self, $y) = @_;
        $self->{x} + $y;
    }
}

sub solve_me_first {
    my ($x, $y) = @_;
    Adder->new($x)->plus($y);
}

say solve_me_first(<<>>, <<>>);
