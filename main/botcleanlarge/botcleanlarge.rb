#!/usr/bin/env ruby
$VERBOSE = true

def read_record
  gets.split.map!(&:to_i)
end

bi, bj = read_record

height, width = read_record
is = 0...height
js = 0...width

raise 'bot outside board' unless is.include?(bi) && js.include?(bj)

di = dj = nil
min_distance = Float::INFINITY

is.each do |i|
  row = gets.strip
  raise 'wrong row length' if row.length != width

  row.each_char.with_index.select { |e, _| e == 'd' }.each do |_, j|
    distance = (bi - i).abs + (bj - j).abs # taxicab metric
    next unless distance < min_distance

    min_distance = distance
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
