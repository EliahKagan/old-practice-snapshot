gets.to_i.times do
  n, k = gets.split.map(&:to_i)
  puts(k < n / 2 ? 1 + k * 2 : (n - k - 1) * 2)
end
