#!/usr/bin/env ruby
$VERBOSE = true

class Foo
  def initialize(x, y)
    @x = x
    @y = y
  end
end

class Bar < Foo
  def to_s
    "(#{@x}, #{@y})"
  end
end

z = Bar.new(10, 20)
puts z
