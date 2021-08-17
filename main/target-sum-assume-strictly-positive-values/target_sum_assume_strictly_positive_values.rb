def count_01_knapsack_ways(values, target)
  memo = {}

  solve = lambda do |index, subtot|
    return 1 if subtot.zero?
    return 0 if index == values.length

    key = [index, subtot].freeze
    count = memo[key]
    return count if count

    count = solve.call(index + 1, subtot)

    subtot -= values[index]
    count += solve.call(index + 1, subtot) unless subtot.negative?

    memo[key] = count
  end

  solve.call(0, target)
end

# Should really be called count_target_sum_ways.
# @param {Integer[]} nums
# @param {Integer} s
# @return {Integer}
def find_target_sum_ways(nums, s)
  # Start with all the signs negative. Then solve the 0-1 knapsack problem with
  # doubled terms (-x + 2x = +x).
  s += nums.sum
  nums.map! { |x| x * 2 }
  count_01_knapsack_ways(nums, s)
end
