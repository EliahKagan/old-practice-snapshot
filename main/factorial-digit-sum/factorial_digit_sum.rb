#!/usr/bin/env ruby
$VERBOSE = true

ARGV.each do |n|
  factorial = (2..Integer(n)).reduce(1, :*)
  puts factorial.to_s.chars.map(&:to_i).reduce(0, :+)
end
