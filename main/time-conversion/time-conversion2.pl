#!/usr/bin/env perl

use strict;
use warnings;
use Time::Piece;

chomp(my $r = <>);
print Time::Piece->strptime($r, '%r')->strftime('%T'), "\n";
