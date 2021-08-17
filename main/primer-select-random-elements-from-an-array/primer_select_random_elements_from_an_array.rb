def random_select(array, n)
  n.times.map { array[rand(array.size)] }.to_a
end
