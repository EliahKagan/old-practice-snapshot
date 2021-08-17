#!/usr/bin/perl

use strict;
use warnings;

my $n = <>;
printf "%*s\n", $n, '#' x $_ for 1..$n;
