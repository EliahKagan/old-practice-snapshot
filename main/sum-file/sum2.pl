#!/usr/bin/perl

use strict;
use warnings;
use 5.010;

my $acc = 0;
$acc += $_ while (<>);
say $acc;
