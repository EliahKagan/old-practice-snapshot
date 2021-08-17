FG_CHAR = '1'.freeze
BG_CHAR = '_'.freeze

# methods to use a hash as a collection of pairs to draw
class Hash
  def populate(iterations, # number of iterations remaning, including this one
               distance, # vertical displacement of trunk, then again of branch
               *coords) # most recently drawn col/row, right/up from the origin
    return unless iterations > 0
    xcoord, ycoord = coords

    distance.times { self[[xcoord, ycoord += 1]] = FG_CHAR } # populating up
    populate_left(iterations, distance, xcoord, ycoord)
    populate_right(iterations, distance, xcoord, ycoord)
  end

  def populate_left(iterations, distance, *coords) # nb comments on populate()
    xcoord, ycoord = coords
    distance.times { self[[xcoord -= 1, ycoord += 1]] = FG_CHAR } # left, up
    populate_next(iterations, distance, xcoord, ycoord)
  end

  def populate_right(iterations, distance, *coords) # nb comments on populate()
    xcoord, ycoord = coords
    distance.times { self[[xcoord += 1, ycoord += 1]] = FG_CHAR } # right, up
    populate_next(iterations, distance, xcoord, ycoord)
  end

  def populate_next(iterations, distance, *coords) # nb comments on populate()
    populate(iterations - 1, distance / 2, *coords)
  end
end

pixels = Hash.new(BG_CHAR)
pixels.populate(gets.to_i, 16, 49, -1)

62.downto(0) do |y|
  0.upto(99) { |x| print pixels[[x, y]] }
  puts
end
