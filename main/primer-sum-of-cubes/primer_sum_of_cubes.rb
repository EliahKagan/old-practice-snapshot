def sum_of_cubes(a, b)
  (a..b).map { |x| x**3 }.reduce(0, :+)
end
