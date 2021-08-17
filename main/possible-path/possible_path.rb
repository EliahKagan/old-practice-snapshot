def gcd(m, n)
  n == 0 ? m : gcd(n, m % n)
end

gets.to_i.times do
  a, b, x, y = gets.split(' ').map(&:to_i)
  puts gcd(a, b) == gcd(x, y) ? 'YES' : 'NO'
end
