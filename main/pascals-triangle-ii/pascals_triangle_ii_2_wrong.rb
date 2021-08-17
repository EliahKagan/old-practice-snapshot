# @param {Integer} row_index
# @return {Integer[]}
def get_row(row_index)
  return [] if row_index < 0

  row = Array.new(row_index + 1, 1)

  2.upto(row_index) do |i|
    i.downto(1) { |j| row[j] += row[j - 1] }
  end

  row
end
