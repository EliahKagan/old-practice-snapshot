def kaprekar?(k)
  s = (k * k).to_s
  h = s.length / 2
  s[0...h].to_i + s[h..-1].to_i == k
end
