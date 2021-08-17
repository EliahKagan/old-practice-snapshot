# A cache of key-value mappings with a least-recently-used invalidation policy.
# This code takes advantage of how the Hash type in Ruby 1.9 and higher is
# officially guaranteed to maintain insertion order. (In MRI 1.9+ they happen
# to be implemented the same way I would otherwise implement an LRU cache: by
# maintaining both a hash table and circular doubly linked list.)
class LRUCache
  NOT_FOUND = -1
  private_constant :NOT_FOUND

  # :type capacity: Integer
  def initialize(capacity)
    raise ArgumentError, 'capacity must be positive' unless capacity.positive?
    @capacity = capacity
    @table = {}
  end

  # :type key: Integer
  # :rtype: Integer
  def get(key)
    value = @table.delete(key)
    return NOT_FOUND if value.nil?
    @table[key] = value
  end

  # :type key: Integer
  # :type value: Integer
  # :rtype: Void
  def put(key, value)
    @table.shift if @table.delete(key).nil? && @table.length == @capacity
    @table[key] = value
  end
end

# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache.new(capacity)
# param_1 = obj.get(key)
# obj.put(key, value)
