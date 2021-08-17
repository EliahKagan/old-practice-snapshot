#!/usr/bin/env ruby
$VERBOSE = true

SIZE = 5
RANGE = 0...SIZE

bi, bj = gets.split.map(&:to_i)
raise 'bot outside board' unless RANGE.include?(bi) && RANGE.include?(bj)

di = dj = nil
best_distance = Float::INFINITY

RANGE.each do |i|
  row = gets.strip
  raise 'wrong row length' if row.length != SIZE

  row.each_char.with_index.select { |e, _| e == 'd' }.each do |_, j|
    distance = (bi - i).abs + (bj - j).abs # taxicab metric
    next unless distance < best_distance

    best_distance = distance
    di = i
    dj = j
  end
end

raise 'board is already clean!' unless di

if bi < di
  puts 'DOWN'
elsif bi > di
  puts 'UP'
elsif bj < dj
  puts 'RIGHT'
elsif bj > dj
  puts 'LEFT'
else
  puts 'CLEAN'
end
