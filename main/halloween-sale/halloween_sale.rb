#!/usr/bin/env ruby
$VERBOSE = true

# Reads a whitespace-separated record of integers.
def read_record
  gets.split.map!(&:to_i)
end

# Counts how many games it is possible to buy.
def count_games(p, d, m, s)
  raise 'p must not be less than m' if p < m

  count = 0

  while p >= m
    return count if (s -= p).negative?
    count += 1
    p -= d
  end

  count + s / m
end

puts count_games(*read_record)
