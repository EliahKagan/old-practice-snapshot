#!/usr/bin/env perl

use strict;
use warnings;

my $n = <>;
for my $i (1..$n) { printf "%*s\n", $n, q{#} x $i }
