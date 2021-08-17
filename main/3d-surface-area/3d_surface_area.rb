#!/usr/bin/env ruby
$VERBOSE = true

def read_record
  gets.split.map!(&:to_i)
end

def read_padded_row(width)
  row = read_record
  raise 'wrong row width' if row.size != width
  row.unshift(0).push(0).freeze
end

def read_padded_matrix(height, width)
  margin = Array.new(width + 2, 0).freeze
  rows = (0...height).map { read_padded_row(width) }
  rows.unshift(margin).push(margin).freeze
end

height, width = read_record
grid = read_padded_matrix(height, width)

area = height * width * 2 # the top and bottom faces

(1...grid.size).each do |i|
  (1...grid[i].size).each do |j|
    area += (grid[i][j - 1] - grid[i][j]).abs +
            (grid[i - 1][j] - grid[i][j]).abs
  end
end

puts area
