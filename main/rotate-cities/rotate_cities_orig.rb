#!/usr/bin/env ruby
$VERBOSE = true

def each_rotation(text)
  text.length.times { |i| yield text[i..-1] + text[0...i] }
end

def group_by_rotations(cities)
  results = []
  map = {}

  cities.each do |city|
    key = city.downcase.freeze

    row = map[key]
    if row.nil?
      row = []
      results << row
      each_rotation(key) { |rot| map[rot] = row }
    end

    row << city
  end

  results
end

a = %w[Tokyo London Rome Donlon Kyoto Paris]
p group_by_rotations(a)
