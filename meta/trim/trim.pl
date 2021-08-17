#!/usr/bin/env perl

use strict;
use warnings;

my $s = <STDIN>;
$s =~ s/^\s+//;
$s =~ s/\s+$//;

print "[$s]\n";
