#!/usr/bin/perl

use strict;
use warnings;
use 5.010;
use bigint;

<>; # don't need n
my $acc = 0;
$acc += $_ for split ' ', <>;
say $acc;
