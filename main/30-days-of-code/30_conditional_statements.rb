n = gets.to_i
puts(n.odd? || (6 <= n && n <= 20) ? 'Weird' : 'Not Weird')
