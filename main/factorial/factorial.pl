#!/usr/bin/env perl

use strict;
use warnings;
use feature qw(say);
use bigint;

for my $arg (@ARGV) {
    say(($arg + 0)->bfac());
}
