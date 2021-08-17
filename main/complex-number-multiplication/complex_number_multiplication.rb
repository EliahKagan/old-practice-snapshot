def parse(z)
  z.sub('+-', '-').to_c
end

# @param {String} a
# @param {String} b
# @return {String}
def complex_number_multiply(w, z)
  res = parse(w) * parse(z)
  "#{res.real}+#{res.imag}i"
end
