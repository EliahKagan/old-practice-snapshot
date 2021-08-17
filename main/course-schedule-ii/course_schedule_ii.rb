def adjacency_list(vertex_count, edges)
  adj = Array.new(vertex_count) { [] }
  edges.each { |dest, src| adj[src] << dest }
  adj
end

def topological_sort(adj)
  vis = Array.new(adj.size, :white)
  out = []

  dfs = proc do |src|
    case vis[src]
    when :white
      vis[src] = :gray
      adj[src].each(&dfs)
      vis[src] = :black
      out << src
    when :gray
      return nil
    when :black
      next
    else
      raise 'Internal error: invalid visitation state'
    end
  end

  adj.size.times(&dfs)
  out.reverse!
end

# @param {Integer} num_courses
# @param {Integer[][]} prerequisites
# @return {Integer[]}
def find_order(num_courses, prerequisites)
  topological_sort(adjacency_list(num_courses, prerequisites)) || []
end
