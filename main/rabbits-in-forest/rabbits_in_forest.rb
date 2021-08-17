# Extension for rounding to the nearest value not less.
class Integer
  def ceil_by(epsilon)
    (to_f / epsilon).ceil * epsilon
  end
end

# @param {Integer[]} answers
# @return {Integer}
def num_rabbits(answers)
  table = Hash.new(0)
  answers.each { |ans| table[ans + 1] += 1 }
  table.sum { |size, freq| freq.ceil_by(size) }
end
