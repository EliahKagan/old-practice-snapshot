# A node for a circular doubly linked list.
class Node
  attr_reader :left, :right
  attr_accessor :key, :value

  def initialize(key = nil, value = nil)
    @left = @right = self

    @key = key
    @value = value
  end

  def splice_right(node)
    node.detach

    node.right = @right
    node.left = self

    @right = @right.left = node
  end

  protected

  attr_writer :left, :right

  def detach
    @left.right = @right
    @right.left = @left

    @left = @right = self
  end
end

NOT_FOUND = -1

# A cache of key-value mappings with a least-recently-used invalidation policy.
class LRUCache
  # :type capacity: Integer
  def initialize(capacity)
    raise ArgumentError, 'capacity must be positive' unless capacity.positive?
    @capacity = capacity
    @size = 0
    @list = Node.new # sentinel node
    @lookup = {} # maps keys to nodes
  end

  # :type key: Integer
  # :rtype: Integer
  def get(key)
    node = @lookup[key]
    return NOT_FOUND unless node
    bump(node)
    node.value
  end

  # :type key: Integer
  # :type value: Integer
  # :rtype: Void
  def put(key, value)
    node = @lookup[key]

    if node
      node.value = value
    elsif @size == @capacity
      node = @list.left
      @lookup.delete(node.key)

      node.key = key
      node.value = value

      @lookup[key] = node
    else
      raise 'Internal error: size exceeds capacity!' unless @size < @capacity

      @size += 1
      @lookup[key] = node = Node.new(key, value)
    end

    bump(node)
  end

  private def bump(node)
    @list.splice_right(node)
  end
end

# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache.new(capacity)
# param_1 = obj.get(key)
# obj.put(key, value)
