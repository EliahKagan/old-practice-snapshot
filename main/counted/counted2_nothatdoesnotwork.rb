#!/usr/bin/env ruby
$VERBOSE = true

class Counted
end

class << Counted
  attr_accessor :count

  @count = 0
end

# A class that increments a counter each time an object is constructed.
class Counted
  def initialize
    @id = Counted.count
    Counted.count += 1
  end
end

x = Counted.new
p x
