def height_after_growth(cycles, height = 1, season = :spring)
  raise 'need cycles nonnegative, height positive' if cycles < 0 || height < 1

  return height if cycles == 0

  case season
  when :spring then height_after_growth(cycles - 1, height * 2, :summer)
  when :summer then height_after_growth(cycles - 1, height + 1, :spring)
  else              raise 'only :summer and :spring seasons are recognized'
  end
end

gets.to_i.times do
  puts height_after_growth(gets.to_i)
end
