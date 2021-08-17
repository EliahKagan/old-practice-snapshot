#!/usr/bin/env ruby
$VERBOSE = true

require_relative 'all_oone_data_structure'

# Extension for obtaining debugging information on a Node, from its sentinel.
class Node
  def to_s
    require_sentinel

    parts = []
    cur = self
    parts.push(cur.serialize) while (cur = cur.next) != self
    parts.join('; ') + '.'
  end

  protected def serialize
    "#{@value}:#{@keys.to_a.join(',')}"
  end
end

# Extension for obtaining debugging information on the stored sentinel node.
class AllOne
  def to_s
    @sentinel.to_s
  end
end

ao = AllOne.new
puts ao
ao.inc('foo')
puts ao
ao.inc('bar')
puts ao
ao.inc('foo')
puts ao
ao.dec('bar')
puts ao
ao.inc('baz')
puts ao
ao.dec('foo')
puts ao
ao.dec('foo')
puts ao
ao.dec('foo')
puts ao
