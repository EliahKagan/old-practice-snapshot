def non_duplicated_values(values)
  counts = Hash.new(0)
  values.each { |x| counts[x] += 1 }
  values.select { |x| counts[x] == 1 }
end
