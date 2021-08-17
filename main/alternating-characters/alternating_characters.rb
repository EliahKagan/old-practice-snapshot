gets.to_i.times do
  puts gets.scan(/(.)(?=\1)/).size
end
