h.n = gets.to_i

sum = (0...n).reduce(0) do |s, i|
  row = gets.split(' ')
  s + row[i].to_i - row[n - i - 1].to_i
end

puts sum.abs
