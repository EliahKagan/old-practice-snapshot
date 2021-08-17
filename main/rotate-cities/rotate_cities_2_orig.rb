#!/usr/bin/env ruby
$VERBOSE = true

def each_rotation(text)
  text.length.times { |i| yield text[i..-1] + text[0...i] }
end

def find_by_rotation(map, key)
  each_rotation(key) do |rot|
    val = map[rot]
    return val unless val.nil?
  end

  nil
end

def group_by_rotations(cities)
  results = []
  map = {}

  cities.each do |city|
    key = city.downcase.freeze

    row = find_by_rotation(map, key)
    if row.nil?
      row = []
      results << row
      map[key] = row
    end

    row << city
  end

  results
end

a = %w[Tokyo London Rome Donlon Kyoto Paris]
p group_by_rotations(a)
