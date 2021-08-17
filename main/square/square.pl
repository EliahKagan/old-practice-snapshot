#!/usr/bin/perl

use strict;
use warnings;
use 5.010;

# while (<>) uses <> in a scalar context, reading a new line into $_ at the top
# of each iteration of the loop. This performs the action immeidately after
# reading each line,  before reading the next line. In contrast, for (<>) uses
# <> in a list context, reading all remaining lines and then, after they have
# all been read, binding $_ to each one and performing the action on it.
say $_ * $_ while (<>);
