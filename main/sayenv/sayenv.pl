#!/usr/bin/env perl

use strict;
use warnings;

if (!@ARGV) {  # got no arguments, so print the whole environment
    for my $key (sort keys %ENV) {
        print "$key=$ENV{$key}\n";
    }

    exit 0;
}

my $got_key_not_found = 0;

for my $key (@ARGV) {
    if (exists $ENV{$key}) {
        print "$ENV{$key}\n";
    } else {
        $got_key_not_found = 1;
    }
}

exit $got_key_not_found;
