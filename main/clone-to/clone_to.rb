#!/usr/bin/env ruby
$VERBOSE = true

# A simple wrapper for a value, able to clone the value to other such warppers.
class Foo
  attr_reader :value

  def initialize(start_value)
    @value = start_value
  end

  def to_s
    "Foo(#{@value})"
  end

  def clone_to(other)
    other.value = @value
  end

  protected

  attr_writer :value
end

x = Foo.new(10)
y = Foo.new(20)
puts "#{x}, #{y}"

x.clone_to(y)
puts "#{x}, #{y}"

puts
puts y.value

puts
puts 'We should get an error now...'
y.value = 30 # should fail
