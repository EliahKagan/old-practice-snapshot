def read_lines(count)
  lines = []
  count.times { lines.push(gets.chomp) }
  lines
end

def read_grid
  height, width = gets.split(' ').map(&:to_i)
  grid = read_lines(height)
  raise 'got incorrect-width row' unless grid.all? { |row| row.size == width }
  grid
end

# instance methods for subgrid-matching (where grids are arrays of strings)
class Array
  def height
    size
  end

  def width
    self[0].size
  end

  def lower_subgrid?(row_index, col_index, grid)
    grid_width = grid.width

    (1...grid.height).all? do |offset|
      self[row_index + offset][col_index, grid_width] == grid[offset]
    end
  end

  def subgrid_at_row?(row_index, grid)
    col_index = 0

    while (col_index = self[row_index].index(grid[0], col_index)) # got match
      return true if lower_subgrid?(row_index, col_index, grid)
      col_index += 1
    end

    false
  end

  def subgrid_anywhere?(grid)
    vrange = 0..(height - grid.height)
    vrange.any? { |row_index| subgrid_at_row?(row_index, grid) }
  end
end

gets.to_i.times do
  major = read_grid
  minor = read_grid
  puts major.subgrid_anywhere?(minor) ? 'YES' : 'NO'
end
