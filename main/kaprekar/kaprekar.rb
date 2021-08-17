def kaprekar?(k)
  str = (k * k).to_s
  mid = str.size / 2
  str[0...mid].to_i + str[mid..-1].to_i == k
end
