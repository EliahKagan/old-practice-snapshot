#!/usr/bin/env ruby
$VERBOSE = true

kitty_toys = [
  { shape: 'sock', fabric: 'cashmere' },
  { shape: 'mouse', fabric: 'calico' },
  { shape: 'eggroll', fabric: 'chenelle' }
]

%i[shape fabric].each do |key|
  puts "By #{key.capitalize}:"
  kitty_toys.sort_by { |toy| toy[key] }.each do |toy|
    puts "    Blixy has a #{toy[:shape]} made of #{toy[:fabric]}."
  end
  puts
end

non_eggroll = 0
kitty_toys.each do |toy|
  next if toy[:shape] == 'eggroll'
  puts "...counting a #{toy[:fabric]} non-eggroll..."
  non_eggroll += 1
end
puts "Found #{non_eggroll} non-eggroll#{non_eggroll == 1 ? '' : 's'}."
puts

puts "Here are the toys, but if I see anything chenelle I'm bailing!"
kitty_toys.each do |toy|
  break if toy[:fabric] == 'chenelle'
  p toy
end
