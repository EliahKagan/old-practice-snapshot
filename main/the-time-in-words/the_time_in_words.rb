def hour(hr)
  case hr
  when 1 then 'one'
  when 2 then 'two'
  when 3 then 'three'
  when 4 then 'four'
  when 5 then 'five'
  when 6 then 'six'
  when 7 then 'seven'
  when 8 then 'eight'
  when 9 then 'nine'
  when 10 then 'ten'
  when 11 then 'eleven'
  when 12 then 'twelve'
  else raise 'hour text lookup failed'
  end
end

def minute(min)
  case min
  when 1 then 'one minute'
  when 2 then 'two minutes'
  when 3 then 'three minutes'
  when 4 then 'four minutes'
  when 5 then 'five minutes'
  when 6 then 'six minutes'
  when 7 then 'seven minutes'
  when 8 then 'eight minutes'
  when 9 then 'nine minutes'
  when 10 then 'ten minutes'
  when 11 then 'eleven minutes'
  when 12 then 'twelve minutes'
  when 13 then 'thirteen minutes'
  when 14 then 'fourteen minutes'
  when 15 then 'quarter'
  when 16 then 'sixteen minutes'
  when 17 then 'seventeen minutes'
  when 18 then 'eighteen minutes'
  when 19 then 'nineteen minutes'
  when 20 then 'twenty minutes'
  when 21 then 'twenty one minutes'
  when 22 then 'twenty two minutes'
  when 23 then 'twenty three minutes'
  when 24 then 'twenty four minutes'
  when 25 then 'twenty five minutes'
  when 26 then 'twenty six minutes'
  when 27 then 'twenty seven minutes'
  when 28 then 'twenty eight minnutes'
  when 29 then 'twenty nine minutes'
  when 30 then 'half'
  else raise 'minute text lookup failed'
  end
end

def time(hr, min)
  return "#{hour(hr)} o' clock" if min == 0
  return "#{minute(min)} past #{hour(hr)}" if min <= 30
  "#{minute(60 - min)} to #{hour(hr + 1)}"
end

hr = gets.to_i
min = gets.to_i
puts time(hr, min)
