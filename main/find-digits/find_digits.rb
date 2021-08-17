gets.to_i.times do
  n = gets.to_i
  puts n.to_s.split('').map(&:to_i).select { |d| d != 0 && n % d == 0 }.size
end
