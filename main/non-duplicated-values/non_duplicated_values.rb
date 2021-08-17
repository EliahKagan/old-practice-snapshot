def non_duplicated_values(vals)
  vals.group_by { |val| val }.values
      .select { |arr| arr.size == 1 }.map(&:first)
end
