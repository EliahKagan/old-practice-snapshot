# recursive factorial method for Integer type, just for fun
class Integer
  def factorial
    self < 2 ? 1 : self * (self - 1).factorial
  end
end

puts gets.to_i.factorial
