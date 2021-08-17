n, m = gets.split(' ').map(&:to_i)
colrange = (0...m)

rows = []
n.times { rows.push(gets.to_i(2)) }

topics = 0
teams = 0

0.upto(n - 2) do |i|
  (i + 1).upto(n - 1) do |j|
    disj = rows[i] | rows[j]
    count = colrange.count { |k| disj[k] == 1 }

    next if count < topics

    if count == topics
      teams += 1
    else
      topics = count
      teams = 1
    end
  end
end

puts topics, teams
