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

  def subgrid_at_pos?(grid, pos)
    row_index, col_index = pos
    rows = self[row_index, grid.height]
    rows.map { |row| row[col_index, grid.width] } == grid
  end

  def subgrid_at_row?(grid, row_index)
    hrange = 0..(width - grid.width)
    hrange.any? { |col_index| subgrid_at_pos?(grid, [row_index, col_index]) }
  end

  def subgrid_anywhere?(grid)
    vrange = 0..(height - grid.height)
    vrange.any? { |row_index| subgrid_at_row?(grid, row_index) }
  end
end

gets.to_i.times do
  major = read_grid
  minor = read_grid
  puts major.subgrid_anywhere?(minor) ? 'YES' : 'NO'
end
