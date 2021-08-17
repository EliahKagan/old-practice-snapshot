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

# An element of a row of an adjacency list of a weighted directed graph.
Neighbor = Struct.new(:dest, :weight)

FIRST_VERTEX = 1 # The lowest vertex number used.

UNREACHABLE_COST = -1 # The path cost displayed in lieu of Float::INFINITY.

def adjacency_list(edges, vertex_count)
  adj = Array.new(vertex_count) { [] }
  FIRST_VERTEX.times { adj.unshift(nil) }
  edges.each { |src, dest, weight| adj[src] << Neighbor.new(dest, weight) }
  adj
end

def max_optimal_path_cost(adj, start)
  heap = PrimHeap.new(FIRST_VERTEX, adj.size - 1)
  heap.decrease(start, 0)
  cost = Float::INFINITY

  until heap.empty?
    src, cost = *heap.pop
    break if cost == Float::INFINITY

    adj[src].each do |neighbor|
      heap.decrease(neighbor.dest, cost + neighbor.weight)
    end
  end

  cost == Float::INFINITY ? UNREACHABLE_COST : cost
end

# @param {Integer[][]} times
# @param {Integer} n
# @param {Integer} k
# @return {Integer}
def network_delay_time(times, n, k)
  max_optimal_path_cost(adjacency_list(times, n), k)
end
