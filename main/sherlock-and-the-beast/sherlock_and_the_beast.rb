def max_decent(width)
  width.downto(0) do |fives|
    threes = width - fives
    decent = fives % 3 == 0 && threes % 5 == 0
    return '5' * fives + '3' * threes if decent
  end

  '-1'
end

gets.to_i.times do
  puts max_decent(gets.to_i)
end
