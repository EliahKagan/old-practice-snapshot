N = 6
RANGE = 1..(N - 2)

# method to treat array of arrays as grid of numbers and compute hourglass sums
class Array
  def hourglass_sum(row_index, col_index)
    above, here, below = self[row_index - 1, 3]
    sum = here[col_index]
    [above, below].each { |row| sum += row[col_index - 1, 3].reduce(:+) }
    sum
  end
end

a = (1..N).map { gets.split(' ').map(&:to_i) }
puts RANGE.map { |i| RANGE.map { |j| a.hourglass_sum(i, j) }.max }.max
