#!/usr/bin/env ruby
$VERBOSE = true

def each_rotation(text)
  text.length.times { |i| yield text[i..-1] + text[0...i] }
end

def find_or_create_row(results, map, key)
  row = map[key]
  return row unless row.nil?

  row = []
  results << row
  each_rotation(key) { |rot| map[rot] = row }

  row
end

def group_by_rotations(cities)
  results = []
  map = {}

  cities.each do |city|
    find_or_create_row(results, map, city.downcase.freeze) << city
  end

  results
end

a = %w[Tokyo London Rome Donlon Kyoto Paris]
p group_by_rotations(a)
