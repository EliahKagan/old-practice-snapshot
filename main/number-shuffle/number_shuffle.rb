def number_shuffle(number)
  number.to_s.chars.permutation.to_a
        .map(&:join).map(&:to_i).sort!.uniq
end
