# Enumerates numbers in a range, squaring odds and leaving evens unchanged.
class OddSquarer
  include Enumerable

  def initialize(low, high)
    @range = low..high
  end

  def each
    return to_enum unless block_given?
    @range.each { |i| yield i.odd? ? i * i : i }
  end
end
