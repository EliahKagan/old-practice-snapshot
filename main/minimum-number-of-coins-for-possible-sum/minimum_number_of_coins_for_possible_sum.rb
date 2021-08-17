#!/usr/bin/env ruby
$VERBOSE = true

def min_combo_size(coins, total)
  memo = {}

  solve = lambda do |index, subtot|
    return 0 if subtot.zero?
    return nil if index == coins.size

    key = [index, subtot].freeze
    size = memo[key]
    return size if size

    next_subtots = subtot.step(0, -coins[index])
    next_index = index + 1

    sizes = next_subtots.with_index.map do |next_subtot, delta|
      next_size = solve.call(next_index, next_subtot)
      delta + next_size if next_size
    end

    size = sizes.reject(&:nil?).min
    memo[key] = size if size
  end

  solve.call(0, total)
end

def read_record
  gets.split.map!(&:to_i)
end

_, total = read_record # don't need record length (n), but do need total (s)
coins = read_record
puts min_combo_size(coins, total) || -1
