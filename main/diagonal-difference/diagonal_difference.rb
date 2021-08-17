sum = 0

n = gets.to_i
(0...n).each do |i|
  row = gets.split(' ')
  sum += row[i].to_i - row[n - i - 1].to_i
end

puts sum.abs
