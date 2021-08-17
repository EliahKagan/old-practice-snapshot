# methods to treat Integer as bitset
class Integer
  def cardinality
    to_s(2).count('1') # may require optimization
  end
end

n = gets.split(' ').first.to_i # only need n of [n, m]
rows = []
n.times { rows.push(gets.to_i(2)) }

topics = 0
teams = 0

0.upto(n - 2) do |i|
  (i + 1).upto(n - 1) do |j|
    count = (rows[i] | rows[j]).cardinality

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
