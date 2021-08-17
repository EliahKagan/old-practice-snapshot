n = gets.to_i
id = (1..n).to_a
fn = gets.split.map(&:to_i).unshift(nil)
puts(id.map { |i| fn[fn[i]] } == id ? 'YES' : 'NO')
