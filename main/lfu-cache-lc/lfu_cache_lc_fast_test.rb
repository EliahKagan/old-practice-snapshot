#!/usr/bin/env ruby
$VERBOSE = true

require_relative 'lfu_cache_lc_fast'

# Extension for obtaining debugging information through a sentinel node.
class Node
  def to_s
    require_sentinel

    parts = []
    cur = self
    parts.push(cur.serialize) while (cur = cur.next) != self
    parts.join('; ') + '.'
  end

  protected def serialize
    "[#{@frequency}]#{serialize_mappings}"
  end

  private def serialize_mappings
    @mappings.map { |k, v| "#{k}:#{v}" }.join(',')
  end
end

# Extension for obtaining debugging information on the stored sentinel node.
class LFUCache
  def to_s
    @sentinel.to_s
  end
end

cache = LFUCache.new(2)
puts cache
cache.put(1, 1)
puts cache
cache.put(2, 2)
puts cache
p cache.get(1)
puts cache
cache.put(3, 3)
puts cache
p cache.get(2)
puts cache
p cache.get(3)
puts cache
cache.put(4, 4)
puts cache
p cache.get(1)
puts cache
p cache.get(3)
puts cache
p cache.get(4)
puts cache
