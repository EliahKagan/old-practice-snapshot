#!/usr/bin/env ruby
$VERBOSE = true

size = gets.to_i
mi, mj = gets.split.map(&:to_i)
pi = pj = nil

(0...size).each do |i|
  row = gets.strip
  raise 'wrong row length' if row.length != size

  row.each_char.each_with_index do |e, j|
    case e
    when '-'
      next
    when 'm'
      raise 'inconsistent bot starting positions' if mi != i || mj != j
    when 'p'
      raise 'multiple princess starting positions' if pi
      pi = i
      pj = j
    else
      raise 'unrecognized character'
    end
  end
end

raise 'no princess position' unless pi

if mi < pi
  puts 'DOWN'
elsif mi > pi
  puts 'UP'
elsif mj < pj
  puts 'RIGHT'
elsif mj > pj
  puts 'LEFT'
else
  raise 'the bot has already reached the princess!'
end
