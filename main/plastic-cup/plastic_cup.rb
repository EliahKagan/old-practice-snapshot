#!/usr/bin/env ruby
$VERBOSE = true

plastic_cup = nil

define_method :test_charge do
  puts 'Testing...'
  puts "Plastic cup is on the up 'n' up!" if plastic_cup
  puts
end

test_charge

plastic_cup = true
test_charge

plastic_cup = false
test_charge
