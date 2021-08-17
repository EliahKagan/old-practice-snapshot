def parts(v)
  v.split('.').map!(&:to_i)
end

def make_equal_length(a, b)
  a, b = b, a if a.length < b.length
  b.fill(0, b.length, a.length - b.length)
end

def parse(v1, v2)
  a = parts(v1)
  b = parts(v2)
  make_equal_length(a, b)
  [a, b]
end

# @param {String} version1
# @param {String} version2
# @return {Integer}
def compare_version(version1, version2)
  a, b = parse(version1, version2)
  ret = 0

  a.lazy.zip(b).each do |x, y|
    ret = x <=> y
    break unless ret.zero?
  end

  ret
end
