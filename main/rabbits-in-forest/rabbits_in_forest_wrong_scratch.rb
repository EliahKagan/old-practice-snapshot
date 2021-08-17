#!/usr/bin/env ruby
$VERBOSE = true

# @param {Integer[]} answers
# @return {Integer}
def num_rabbits(answers)
  table = Hash.new(0)
  answers.each { |ans| table[ans + 1] += 1 }
  table.lazy.map(&:max).reduce(0, :+)
end

p num_rabbits([1,0,1,0,0])
