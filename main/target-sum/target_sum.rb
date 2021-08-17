def count_01_combos(values, target)
  memo = {}

  solve = lambda do |index, subtot|
    return 0 if subtot.negative?
    return subtot.zero? ? 1 : 0 if index == values.length

    key = [index, subtot].freeze
    count = memo[key]
    return count if count

    memo[key] = solve.call(index + 1, subtot) +
                solve.call(index + 1, subtot - values[index])
  end

  solve.call(0, target)
end

# Should really be called count_target_sum_ways.
# @param {Integer[]} nums
# @param {Integer} s
# @return {Integer}
def find_target_sum_ways(nums, s)
  # Start with all the signs negative. Then solve the 0-1 coin change problem
  # with doubled terms (this works because: -x + 2x = +x).
  s += nums.sum
  nums.map! { |x| x * 2 }
  count_01_combos(nums, s)
end
