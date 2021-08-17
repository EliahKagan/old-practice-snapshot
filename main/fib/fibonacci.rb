#!/usr/bin/env ruby
$VERBOSE = true

# Enumerable fibonacci sequences.
class Fibonacci
  include Enumerable

  attr_reader :count, :first, :second
  alias size count
  alias length count

  def initialize(count, first = 0, second = 1)
    @count = count
    @first = first
    @second = second
  end

  def each
    return to_enum unless block_given?

    a = @first
    b = @second

    1.upto(@count) do
      yield a
      a, b = b, a + b
    end
  end
end
