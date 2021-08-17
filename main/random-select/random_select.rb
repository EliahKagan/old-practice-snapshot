def random_select(array, n)
  a = []
  n.times { a << array[rand(array.size)] }
  a
end
