def read_record(size)
  gets.split(' ').map(&:to_i).take(size)
end

n, t = read_record(2)
widths = read_record(n)

t.times do
  i, j = read_record(2)
  min = 3
  i.upto(j) { |k| min = widths[k] if widths[k] < min }
  puts min
end
