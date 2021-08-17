h = Hash.new('Not found')

gets.to_i.times do
  name, phone = gets.chomp.split(' ')
  h[name] = "#{name}=#{phone}"
end

while (query = gets)
  puts h[query.chomp]
end
