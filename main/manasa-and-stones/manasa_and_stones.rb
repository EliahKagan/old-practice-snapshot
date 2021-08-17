def possible_final_values(nstones, step_a, step_b)
  return [0] unless nstones > 1
  nhops = nstones - 1
  (0..nhops).map { |hop| step_a * hop + step_b * (nhops - hop) }.sort!.uniq
end

gets.to_i.times do
  n, a, b = (1..3).map { |_| gets }.map(&:to_i)
  puts possible_final_values(n, a, b).join(' ')
end
