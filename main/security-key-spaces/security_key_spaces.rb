a = gets.chomp.split('').map(&:to_i)
e = gets.to_i
puts a.map { |i| (i + e) % 10 }.join('')
