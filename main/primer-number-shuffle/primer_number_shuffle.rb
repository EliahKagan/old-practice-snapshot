def number_shuffle(number)
  number.to_s.each_char.to_a.permutation.
    map(&:join).map(&:to_i).to_a
end
