# @param {Integer[][]} pairs
# @return {Integer}
def find_longest_chain(pairs)
  time = -Float::INFINITY
  count = 0

  pairs.sort_by!(&:last).each do |start, stop|
    next unless time < start
    time = stop
    count += 1
  end

  count
end
