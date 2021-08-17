#!/usr/bin/env ruby
$VERBOSE = true

1.upto(100) do |i|
  print_i = true

  if (i % 3).zero?
    print 'Fizz'
    print_i = false
  end

  if (i % 5).zero?
    print 'Buzz'
    print_i = false
  end

  print i if print_i
  puts
end
