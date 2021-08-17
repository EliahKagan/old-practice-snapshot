# methods for treating arrays as due or returned [day, month, year]
class Array
  def day
    self[0]
  end

  def month
    self[1]
  end

  def year
    self[2]
  end
end

def read_date
  date = gets.split(' ').map(&:to_i)
  raise 'date record needs 3 fields (day, month, year)' unless date.size == 3
  date
end

def fine(returned, due)
  if returned.year < due.year then 0
  elsif returned.year > due.year then 10_000
  elsif returned.month < due.month then 0
  elsif returned.month > due.month then (returned.month - due.month) * 500
  elsif returned.day <= due.day then 0
  else (returned.day - due.day) * 15
  end
end

returned = read_date
due = read_date

puts fine(returned, due)
