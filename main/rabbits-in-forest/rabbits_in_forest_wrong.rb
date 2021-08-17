# @param {Integer[]} answers
# @return {Integer}
def num_rabbits(answers)
  table = Hash.new(0)
  answers.each { |ans| table[ans + 1] += 1 }
  table.lazy.map(&:max).sum
end
