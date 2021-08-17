#!/usr/bin/perl

use strict;
use warnings;
use 5.010;

my ($i, $j) = @ARGV;
say(join(' ', $i > $j ? reverse $j..$i : $i..$j));
