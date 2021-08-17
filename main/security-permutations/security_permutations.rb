n = gets.to_i
fn = gets.split.map(&:to_i).unshift(nil)
(1..n).map { |i| fn[fn[i]] }.each { |k| puts k }
