# factorial method for Integer type
class Integer
  def factorial
    (2..self).reduce(1, :*)
  end
end

puts gets.to_i.factorial
