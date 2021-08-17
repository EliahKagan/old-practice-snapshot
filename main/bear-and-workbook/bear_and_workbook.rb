def read_record(size)
  record = gets.split(' ').map(&:to_i)
  raise 'record size is incorrect' if record.size != size
  raise 'invalid field' unless record.all? { |field| field.between?(1, 100) }
  record
end

n, k = read_record(2)
t = read_record(n).unshift(nil)

specials = 0
page = 0

1.upto(n) do |chapter|
  space = 0

  1.upto(t[chapter]) do |problem|
    if space == 0
      page += 1
      space = k
    end

    space -= 1
    specials += 1 if page == problem
  end
end

puts specials
