# A node representing a value (or a sentinel node).
class ValueNode
  def initialize(value = nil, below = nil, above = nil)
    if value
      raise ArgumentError 'sentinel must be neighborless' if below || above

      @below = @above = self
      @value = @population = nil
    else
      raise ArgumentError 'need exactly one neighbor' unless below ^ above

      if below
        place_above(below)
      else
        place_below(above)
      end

      @value = value
      @population = 1
    end
  end

  #def inc

  protected

  attr_accessor :below, :above

  private

  def place_above(below)
    @below = below
    @above = below.above
    below.above = below.above.below = self
  end

  def place_below(above)
    @below = above.below
    @above = above
    above.below = above.below.above = self
  end

  def sentinel?
    @value.nil?
  end
end

# Counter data structure supporting O(1) insert (inc), remove (dec),
# retrieval of an arbitrary key of maximum frequency, and retrieval of an
# arbitrary key of minimum nonzero frequency.
class AllOne
  # Initialize your data structure here.
  def initialize

  end

  # Inserts a new key <Key> with value 1. Or increments an existing key by 1.
  # :type key: String
  # :rtype: Void
  def inc(key)

  end

  # Decrements an existing key by 1.
  # If Key's value is 1, remove it from the data structure.
  # :type key: String
  # :rtype: Void
  def dec(key)

  end

  # Returns one of the keys with maximal value.
  # :rtype: String
  def get_max_key

  end

  # Returns one of the keys with Minimal value.
  # :rtype: String
  def get_min_key

  end
end

# Your AllOne object will be instantiated and called as such:
# obj = AllOne.new()
# obj.inc(key)
# obj.dec(key)
# param_3 = obj.get_max_key()
# param_4 = obj.get_min_key()
