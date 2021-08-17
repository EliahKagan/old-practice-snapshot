# @param {Integer} row_index
# @return {Integer[]}
def get_row(row_index)
  return [] if row_index < 0

  cur = [1]
  1.upto(row_index) do |i|
    prev = cur
    cur = [1]
    (1...i).each { |j| cur.push(prev[j - 1] + prev[j]) }
    cur.push(1)
  end

  cur
end
