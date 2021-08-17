# @param {Integer} n
# @return {String[]}
def fizz_buzz(n)
  (1..n).map do |i|
    fizz = (i % 3).zero?
    buzz = (i % 5).zero?

    if fizz && buzz
      'FizzBuzz'
    elsif fizz
      'Fizz'
    elsif buzz
      'Buzz'
    else
      i.to_s
    end
  end
end
