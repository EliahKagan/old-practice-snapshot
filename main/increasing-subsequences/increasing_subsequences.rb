# Helper function for find_subsequences. Gets nondecreasing subsequences.
def subsequences(nums, min, start)
  return [[]] if start == nums.size

  cur = nums[start]
  without_cur = subsequences(nums, min, start + 1)
  return without_cur if cur < min

  with_cur = subsequences(nums, cur, start + 1).each { |a| a.unshift(cur) }
  with_cur.concat(without_cur)
  with_cur.uniq!
  with_cur
end

# @param {Integer[]} nums
# @return {Integer[][]}
def find_subsequences(nums)
  ret = subsequences(nums, -Float::INFINITY, 0)
  ret.reject! { |a| a.size < 2 }
  ret
end
