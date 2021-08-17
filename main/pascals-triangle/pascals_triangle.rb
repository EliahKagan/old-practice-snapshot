# @param {Integer} num_rows
# @return {Integer[][]}
def generate(num_rows)
  return [] if num_rows <= 0

  table = [[1]]

  (1...num_rows).each do |i|
    prev = table[-1]

    cur = [1]
    1.upto(i - 1) { |j| cur.push(prev[j - 1] + prev[j]) }
    cur.push(1)

    table.push(cur)
  end

  table
end
