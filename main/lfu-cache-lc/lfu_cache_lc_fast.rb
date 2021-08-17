# A circular doubly linked list node representing a frequency and the "set" of
# key-value mappings that have been accessed exactly thatn number of times.
# This code takes advantage of how Hash in Ruby 1.9+ maintains insertion order.
class Node
  def initialize(frequency = 0)
    @prev = @next = self
    @frequency = frequency
    @mappings = {}
  end

  def sentinel?
    @frequency.zero?
  end

  # When called with a key and value, bumps the key's frequency and sets the
  # new value. When called with just a key (or nil as the value), bumps the
  # key's frequency and keeps the old value. Returns a [node, value] pair as a
  # 2-element Array. If the returned node value is non-nil then the caller
  # must update their frequency-to-node table. The returned value is the value
  # after the operation, regardless of whether or not it was changed.
  def bump(key, value = nil)
    raise ArgumentError, 'nil and false keys are not allowed' unless key
    value ||= @mappings[key]
    @mappings.one? ? bump_unique(key, value) : bump_nonunique(key, value)
  end

  # When called on a sentinel, discards and returns the key of the least
  # frequently bumped mapping. If there is more than one such mapping, then the
  # least recently bumped of them is selected.
  def drop
    require_sentinel
    @next.discard
  end

  protected

  attr_accessor :prev, :next
  attr_reader :frequency

  def detach
    @prev.next = @next
    @next.prev = @prev
    @prev = @next = self
  end

  def add(key, value)
    @mappings[key] = value
    [self, value] # so the key-to-node table can be updated
  end

  def discard
    key, = @mappings.shift
    raise 'Internal error: dicarded key was invalid!' unless key
    detach if @mappings.empty?
    key
  end

  private

  def splice_next(node)
    node.detach
    node.prev = self
    node.next = @next
    @next = @next.prev = node
  end

  def bump_unique(key, value)
    if @next.frequency == @frequency + 1
      node = @next
      detach
      node.add(key, value)
    else
      @frequency += 1
      @mappings[key] = value
      [nil, value] # in this case, the key-to-node table need not be updated
    end
  end

  def bump_nonunique(key, value)
    @mappings.delete(key)
    splice_next(Node.new(@frequency + 1)) if @next.frequency != @frequency + 1
    @next.add(key, value)
  end

  def require_sentinel
    raise 'invalid operation on non-sentinel node' unless sentinel?
  end
end

# A cache of key-value mappings with a least-frequenty-used primary
# invalidation policy, and a least-recently-used tie-breaking policy.
class LFUCache
  NOT_FOUND = -1
  private_constant :NOT_FOUND

  # :type capacity: Integer
  def initialize(capacity)
    raise ArgumentError, 'capacity must be nonnegative' if capacity.negative?
    @capacity = capacity

    if capacity.zero?
      @sentinel = @table = nil
    else
      @sentinel = Node.new
      @table = Hash.new(@sentinel)
    end
  end

  # :type key: Integer
  # :rtype: Integer
  def get(key)
    return NOT_FOUND if trivial?

    node = @table[key]
    node.sentinel? ? NOT_FOUND : access(node, key)
  end

  # :type key: Integer
  # :type value: Integer
  # :rtype: Void
  def put(key, value)
    return if trivial?

    node = @table[key]
    @table.delete(@sentinel.drop) if node.sentinel? && @table.size == @capacity
    access(node, key, value)
  end

  private def trivial?
    @sentinel.nil?
  end

  private def access(node, key, value = nil)
    node, value = node.bump(key, value)
    @table[key] = node if node
    value
  end
end

# Your LFUCache object will be instantiated and called as such:
# obj = LFUCache.new(capacity)
# param_1 = obj.get(key)
# obj.put(key, value)
