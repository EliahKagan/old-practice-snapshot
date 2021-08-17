gets.to_i.times do
  even = ''
  odd = ''
  gets.chomp.each_char.with_index { |c, i| (i.even? ? even : odd) << c }
  printf "%s %s\n", even, odd
end
