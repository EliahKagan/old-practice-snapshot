#!/usr/bin/env perl

use strict;
use warnings;
use bigint;
use List::Util qw(sum);

<>; # don't need N
my @arr = split / /, <>;

print sum(@arr);
