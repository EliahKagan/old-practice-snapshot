# @param {Integer[]} nums
# @return {Integer[][]}
def find_subsequences(nums)
  dfs = lambda do |min, start|
    return [[]] if start == nums.size

    cur = nums[start]
    without_cur = dfs.call(min, start + 1)
    return without_cur if cur < min

    with_cur = dfs.call(cur, start + 1).each { |a| a.unshift(cur) }
    with_cur.concat(without_cur)
    with_cur.uniq!
    with_cur
  end

  ret = dfs.call(-Float::INFINITY, 0)
  ret.reject! { |a| a.size < 2 }
  ret
end
