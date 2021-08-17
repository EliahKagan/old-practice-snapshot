count = gets.to_f
p = 0
n = 0
z = 0

gets.split(' ').map(&:to_i).each do |k|
  if k > 0
    p += 1
  elsif k < 0
    n += 1
  else
    z += 1
  end
end

[p, n, z].each { |k| printf "%f\n", k / count }
