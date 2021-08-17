#!/usr/bin/env ruby
$VERBOSE = true

n = gets.to_i
heights = gets.split.map!(&:to_i)
raise 'wrong record length' if heights.size != n
heights.unshift(0).push(0)

lefts = []
max_area = 0

heights.each_with_index do |right_height, right|
  while !lefts.empty? && heights[lefts.last] > right_height
    left = lefts.pop

    width = right
    width -= 1 + lefts.last unless lefts.empty?

    area = heights[left] * width
    max_area = area if max_area < area
  end

  lefts << right
end

puts max_area
