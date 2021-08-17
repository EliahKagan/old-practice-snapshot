def read_record
  gets.split(' ').map(&:to_i)
end

gets.to_i.times do
  b, w = read_record
  x, y, z = read_record
  puts b * [x, y + z].min + w * [y, x + z].min
end
