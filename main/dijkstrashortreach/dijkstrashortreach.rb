#!/usr/bin/env ruby
$VERBOSE = true

# A (key, value) entry in a PrimHeap.
Entry = Struct.new(:key, :value)

# A binary minheap, modified for use in Prim's or Dijkstra's algorithm.
class PrimHeap
  def initialize(min_key, max_key)
    raise ArgumentError, 'negative length range' if min_key > max_key

    # create and populate the key => index map
    @map = (0..(max_key - min_key)).to_a
    min_key.times { @map.unshift(nil) }

    # create and populate the index => (key, value) entries
    @entries = (min_key..max_key).map { |key| Entry.new(key, Float::INFINITY) }
  end

  def empty?
    @entries.empty?
  end

  def pop
    ret = @entries.first
    @map[ret.key] = nil

    if @entries.one?
      @entries.clear
    else
      @entries[0] = @entries.pop
      sift_down(0)
    end

    ret
  end

  def decrease(key, value)
    child = @map[key]
    return if child.nil?

    ent = @entries[child]
    return if ent.value <= value

    ent.value = value
    sift_up(child)
    nil
  end

  private def sift_up(child)
    until child.zero?
      parent = (child - 1) / 2
      break if order_ok?(parent, child)

      swap(child, parent)
      child = parent
    end

    record(child)
  end

  private def sift_down(parent)
    loop do
      child = pick_child(parent)
      break if child.nil? || order_ok?(parent, child)

      swap(parent, child)
      parent = child
    end

    record(parent)
  end

  private def pick_child(parent)
    left = parent * 2 + 1
    return nil if left >= @entries.size

    right = left + 1
    right == @entries.size || order_ok?(left, right) ? left : right
  end

  private def swap(src, dest)
    @entries[dest], @entries[src] = @entries[src], @entries[dest]
    record(src)
  end

  private def record(src)
    @map[@entries[src].key] = src
  end

  private def order_ok?(parent, child)
    @entries[parent].value <= @entries[child].value
  end
end

# The endpoints of an undirected edge, without weight information.
Endpoints = Struct.new(:u, :v) do
  def initialize(u, v)
    if u > v
      super(v, u)
    else
      super(u, v)
    end

    freeze
  end
end

# An element of a row of an adjacency list of a weighted undirected graph.
Neighbor = Struct.new(:dest, :wt)

def read_record
  gets.split.map!(&:to_i)
end

FIRST_VERTEX = 1 # The lowest vertex number used.

UNREACHABLE_COST = -1 # The fictitious cost displayed for unreachable vertices.

# Creates an adjacency list with all rows empty.
def empty_adjacency_list(vertex_count)
  raise ArgumentError, 'negative vertex count?' if vertex_count.negative?

  adj = Array.new(vertex_count) { [] }
  FIRST_VERTEX.times { adj.unshift(nil) }
  adj
end

# Reads a graph as a hash-based sparse adjacency matrix.
def read_simple_graph_edges(edge_count)
  raise ArgumentError, 'negative edge count?' if edge_count.negative?

  edges = {}

  edge_count.times do
    u, v, wt = read_record
    next if u == v

    uv = Endpoints.new(u, v)
    old_wt = edges[uv]
    edges[uv] = wt if old_wt.nil? || wt < old_wt
  end

  edges
end

# Reads a weighted undirected graph as an adjacency list.
def read_graph
  vertex_count, edge_count = read_record

  adj = empty_adjacency_list(vertex_count)

  read_simple_graph_edges(edge_count).each do |uv, wt|
    u, v = *uv
    adj[u] << Neighbor.new(v, wt)
    adj[v] << Neighbor.new(u, wt)
  end

  adj
end

# Calculates the least cost paths from a given starting vertex, start, to each
# vertex in a graph. Uses Dijkstra's algorithm.
def compute_shortest_reaches(adj, start)
  costs = Array.new(adj.size, UNREACHABLE_COST)

  cost_heap = PrimHeap.new(FIRST_VERTEX, adj.size - 1)
  cost_heap.decrease(start, 0)

  until cost_heap.empty?
    src, src_cost = *cost_heap.pop
    break if src_cost == Float::INFINITY

    costs[src] = src_cost

    adj[src].each do |neighbor|
      cost_heap.decrease(neighbor.dest, src_cost + neighbor.wt)
    end
  end

  costs
end

gets.to_i.times do
  adj = read_graph
  start = gets.to_i
  costs = compute_shortest_reaches(adj, start)
  puts((costs[FIRST_VERTEX...start] + costs[(start + 1)..-1]).join(' '))
end
