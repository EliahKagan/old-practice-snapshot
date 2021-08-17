#!/usr/bin/env perl

use strict;
use warnings;

while (<>) {
    if (/^\s*(?:\((?<area>\d{3})\)\ |(?<area>\d{3})-)
            (?<local>\d{3}-\d{4})\s*$/x) {
        print "$+{local} (area code $+{area})\n";
    }
}
