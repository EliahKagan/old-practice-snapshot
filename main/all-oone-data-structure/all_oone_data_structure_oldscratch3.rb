require 'set'

# A circular doubly linked list node representing a value and its set of keys.
class Node
  attr_reader :prev, :next

  def initialize(value = nil, initial_key = nil)
    @prev = @next = self

    if value
      raise ArgumentError, 'got value without initial key' unless initial_key
      @value = value
      @keys = Set.new
      @keys.add(initial_key)
    else
      raise ArgumentError, 'got initial key without value' if initial_key
      @value = @keys = nil
    end
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
    node.prev = self
    node.next = @next
    @next = @next.prev = node
  end

  def add(key)
    @keys.add(key.freeze)
  end

  def delete(key)
    @keys.delete(key)
  end

  def promote
    @value += 1
  end

  def demote
    @value -= 1
  end

  protected

  attr_accessor :prev, :next
end

# Counter data structure supporting O(1) insert (inc), remove (dec),
# retrieval of an arbitrary key of maximum frequency, and retrieval of an
# arbitrary key of minimum nonzero frequency.
class AllOne
  # Initialize your data structure here.
  def initialize
    @sentinel = Node.new
    @table = {}
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
