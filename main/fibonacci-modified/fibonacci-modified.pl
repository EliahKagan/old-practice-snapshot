#!/usr/bin/env perl

use strict;
use warnings;
use bigint;
use feature qw(say);

sub fibonacci_modified {
    my ($a, $b, $n) = @_;
    
    for (3..$n) {
        ($a, $b) = ($b, $a + $b**2);
    }

    return $b;
}

say fibonacci_modified(<<>> =~ /\S+/gmsx);
