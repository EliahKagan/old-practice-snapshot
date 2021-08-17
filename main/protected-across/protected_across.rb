#!/usr/bin/env ruby
$VERBOSE = true

# A base class with a protected instance method.
class Root
  def initialize(value)
    @value = value
  end

  protected def show
    puts @value
  end
end

# The first derived class.
class Left < Root
end

# The second derived class.
class Right < Root
  def show_other(obj)
    obj.show
  end
end

left = Left.new(10)
right = Right.new(20)
right.show_other(left)
