# methods to identify and generate modified Kaprekar numbers
class Integer
  def modified_kaprekar?
    str = (self * self).to_s
    middle = str.size / 2
    str[0...middle].to_i + str[middle..-1].to_i == self
  end

  def modified_kaprekars_upto(max)
    min, one = self < 9 ? [9, self == 1] : [self, false] # handling 1 specially
    seq = (min..max).select(&:modified_kaprekar?)
    seq.unshift(1) if one
    seq
  end
end

p, q = (1..2).map { gets.to_i }
a = p.modified_kaprekars_upto(q)
puts a.empty? ? 'INVALID RANGE' : a.join(' ')
