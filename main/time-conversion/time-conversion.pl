#!/usr/bin/perl

use strict;
use warnings;
use 5.010;

use Time::Piece;

chomp(my $r = <>);
say Time::Piece->strptime($r, '%r')->strftime('%T');
