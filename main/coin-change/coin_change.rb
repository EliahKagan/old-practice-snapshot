#!/usr/bin/env ruby
$VERBOSE = true

def count_ways(coins, total)
  memo = {}

  solve = lambda do |index, subtot|
    return 1 if subtot.zero?
    return 0 if index == coins.size

    key = [index, subtot].freeze
    count = memo[key]
    return count if count

    count = 0
    value = coins[index]
    index += 1

    until subtot.negative?
      count += solve.call(index, subtot)
      subtot -= value
    end

    memo[key] = count
  end

  solve.call(0, total)
end

def read_record
  gets.split.map!(&:to_i)
end

total, = read_record # need n (total), but not m (record length)
coins = read_record
puts count_ways(coins, total)
