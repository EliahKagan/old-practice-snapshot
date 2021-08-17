n = gets.to_i
a = gets.split(' ').map(&:to_i).take(n).sort!

i = 0
while i != n
  puts n - i
  cut = a[i]
  i += 1 while i != n && a[i] <= cut
  (i...n).each { |j| a[j] -= cut }
end
