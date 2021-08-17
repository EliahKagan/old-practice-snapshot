gets
puts gets.split(' ').map(&:to_i).reduce(0, :+)
