gets.to_i.times do
  s = gets.chomp
  n = s.size

  if n.odd?
    puts '-1'
  else
    m = n / 2
    h = Hash.new 0

    (0...m).each { |i| h[s[i]] += 1 }
    (m...n).each { |i| h[s[i]] -= 1 }

    puts h.values.select { |v| v > 0 }.reduce(0, :+)
  end
end
