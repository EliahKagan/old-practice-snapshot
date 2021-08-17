gets.to_i.times do
  a, b = gets.split(' ').map(&:to_i)
  puts [Math.sqrt(b).floor - Math.sqrt(a).ceil + 1, 0].max
end
