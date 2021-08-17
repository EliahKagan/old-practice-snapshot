#!/usr/bin/env perl

use strict;
use warnings;
use Math::BigInt;

my $n = <>;
print Math::BigInt->new($n)->bfac(), "\n";
