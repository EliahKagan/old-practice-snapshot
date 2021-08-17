def read_record(size)
  record = gets.split.map(&:to_i)
  raise 'input record has incorrect length' unless record.size == size
  record
end

gets.to_i.times do
  n, k = read_record(2)
  puts read_record(n).reject { |time| time > 0 }.size < k ? 'YES' : 'NO'
end
