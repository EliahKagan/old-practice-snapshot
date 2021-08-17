require 'set'

# A circular doubly linked list node representing a value and its set of keys.
class Node
  def initialize(value = 0)
    @prev = @next = self
    @value = value
    @keys = Set.new
  end

  def promote(key)
    @keys.one? ? promote_unique(key) : promote_nonunique(key)
  end

  def demote(key)
    @keys.one? ? demote_unique(key) : demote_nonunique(key)
  end

  def sample_prev
    require_sentinel
    @prev.sample
  end

  def sample_next
    require_sentinel
    @next.sample
  end

  protected

  attr_accessor :prev, :next
  attr_reader :value

  def detach
    @prev.next = @next
    @next.prev = @prev
    @prev = @next = self
  end

  def add(key)
    @keys.add(key)
    self
  end

  def sample
    @keys.first
  end

  private

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

  def promote_unique(key)
    if @next.value == @value + 1
      ret = @next
      detach
      ret.add(key)
    else
      @value += 1
      self
    end
  end

  def promote_nonunique(key)
    @keys.delete(key)
    splice_next(Node.new(@value + 1)) if @next.value != @value + 1
    @next.add(key)
  end

  def demote_unique(key)
    if @value == 1
      detach
      nil
    elsif @prev.value == @value - 1
      ret = @prev
      detach
      ret.add(key)
    else
      @value -= 1
      self
    end
  end

  def demote_nonunique(key)
    @keys.delete(key)
    return nil if @value == 1
    splice_prev(Node.new(@value - 1)) if @prev.value != @value - 1
    @prev.add(key)
  end

  def require_sentinel
    raise 'invalid operation on non-sentinel node' unless @value.zero?
  end
end

# Counter data structure supporting O(1) insert (inc), remove (dec),
# retrieval of an arbitrary key of maximum frequency, and retrieval of an
# arbitrary key of minimum nonzero frequency.
class AllOne
  FALLBACK_KEYSTRING = ''.freeze
  private_constant :FALLBACK_KEYSTRING

  # Initialize your data structure here.
  def initialize
    @sentinel = Node.new
    @table = Hash.new(@sentinel)
  end

  # Inserts a new key <Key> with value 1. Or increments an existing key by 1.
  # :type key: String
  # :rtype: Void
  def inc(key)
    key.freeze
    @table[key] = @table[key].promote(key)
  end

  # Decrements an existing key by 1.
  # If Key's value is 1, remove it from the data structure.
  # :type key: String
  # :rtype: Void
  def dec(key)
    return unless @table.include?(key)

    key.freeze
    node = @table[key].demote(key)

    if node
      @table[key] = node
    else
      @table.delete(key)
    end
  end

  # Returns one of the keys with maximal value.
  # :rtype: String
  def get_max_key
    @sentinel.sample_prev || FALLBACK_KEYSTRING
  end

  # Returns one of the keys with Minimal value.
  # :rtype: String
  def get_min_key
    @sentinel.sample_next || FALLBACK_KEYSTRING
  end
end

# Your AllOne object will be instantiated and called as such:
# obj = AllOne.new()
# obj.inc(key)
# obj.dec(key)
# param_3 = obj.get_max_key()
# param_4 = obj.get_min_key()
