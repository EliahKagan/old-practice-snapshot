def adjacency_list(vertex_count, edges)
  adj = Array.new(vertex_count) { [] }
  edges.each { |dest, src| adj[src] << dest }
  adj
end

State = Struct.new(:vertex, :index)

def topological_sort(adj)
  vis = Array.new(adj.size, :white)
  out = []

  dfs = proc do |start|
    next if vis[start] == :black
    raise 'Internal error: corrupted visitation list' if vis[start] != :white
    vis[start] = :gray
    path = [State.new(start, 0)]

    until path.empty?
      state = path.last
      if state.index == adj[state.vertex].size
        vis[state.vertex] = :black
        path.pop
        out.unshift(state.vertex)
        next
      end

      dest = adj[state.vertex][state.index]
      state.index += 1

      case vis[dest]
      when :white
        vis[dest] = :gray
        path << State.new(dest, 0)
      when :gray
        return nil # got cycle
      when :black
        next
      else
        raise 'Internal error: invalid vistation state'
      end
    end
  end

  adj.size.times(&dfs)
  out
end

# @param {Integer} num_courses
# @param {Integer[][]} prerequisites
# @return {Integer[]}
def find_order(num_courses, prerequisites)
  topological_sort(adjacency_list(num_courses, prerequisites)) || []
end
