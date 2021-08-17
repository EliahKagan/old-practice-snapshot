def number_shuffle(number)
  digits = number.to_s.chars.to_a
  digits.permutation(digits.size).to_a
        .map(&:join).map(&:to_i).sort!.uniq
end
