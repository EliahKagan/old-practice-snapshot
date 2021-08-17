# Base class for nodes of a circular doubly linked list.
class BasicNode
  attr_reader :prev, :next

  def initialize
    @prev = @next = self
  end

  def detach
    @prev.next = @next
    @next.prev = @prev

    @prev = @next = self
  end

  def splice_prev(node)
    node.detach

    node.prev = @prev
    node.next = self

    @prev = @prev.next = node
  end

  def splice_next(node)
    node.detach

    node.next = @next
    node.prev = self

    @next = @next.prev = node
  end

  protected

  attr_writer :prev, :next
end

# A node in a circular doubly linked list of keys.
class KeyNode < BasicNode
  attr_reader :key

  def initialize(key = nil)
    super()
    @key = key
  end
end

# A node in a circular doubly linked list of bins representing values.
class BinNode < BasicNode
  attr_reader :value

  def initialize(value = nil, keys = nil)
    super()
    @value = value
    @keys = keys
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
