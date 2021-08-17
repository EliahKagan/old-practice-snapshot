# Builds an adjacency list for a weighted directed graph.
def adjacency_list(edges, vertex_count)
  adj = Array.new(vertex_count) { [] }
  edges.each { |from, to, weight| adj[from] << [to, weight] }
  adj
end

def cheapest_price(adj, src, dst, max_distance)
  prices = Array.new(adj.size, Float::INFINITY)
  prices[src] = 0
  queue = [[src, 0]]

  max_distance.times do
    break if queue.empty? # a minor optimization

    queue.size.times do
      from, from_price = queue.shift

      adj[from].each do |to, cost|
        to_price = from_price + cost
        next unless to_price < prices[to]

        prices[to] = to_price
        queue << [to, to_price]
      end
    end
  end

  prices[dst]
end

# @param {Integer} n
# @param {Integer[][]} flights
# @param {Integer} src
# @param {Integer} dst
# @param {Integer} k
# @return {Integer}
def find_cheapest_price(n, flights, src, dst, k)
  price = cheapest_price(adjacency_list(flights, n), src, dst, k + 1)
  price == Float::INFINITY ? -1 : price
end
