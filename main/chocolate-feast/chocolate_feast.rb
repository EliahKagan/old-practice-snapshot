gets.to_i.times do
  n, c, m = gets.split(' ').map(&:to_i)

  u = n / c   # total units of chocolate purchased so far
  w = u       # current number of wrappers held

  loop do
    du, w = w.divmod(m)
    break if du == 0
    u += du
    w += du
  end

  puts u
end
