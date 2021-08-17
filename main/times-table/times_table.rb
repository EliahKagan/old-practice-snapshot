#!/usr/bin/env ruby
$VERBOSE = true

# Adjust these constants to set the default range of operand values.
DEFAULT_MIN_FACTOR = 1
DEFAULT_MAX_FACTOR = 12

def die
  abort "Usage:  #{$PROGRAM_NAME} [ [ min_factor ] max_factor ]"
end

def max_product_width(factors)
  acc = 0

  factors.each do |x|
    factors.each do |y|
      cur = (x * y).to_s.length
      acc = cur if acc < cur
    end
  end

  acc
end

begin
  case ARGV.length
  when 0
    min_factor = DEFAULT_MIN_FACTOR
    max_factor = DEFAULT_MAX_FACTOR
  when 1
    min_factor = DEFAULT_MIN_FACTOR
    max_factor = Integer(ARGV[0])
  when 2
    min_factor = Integer(ARGV[0])
    max_factor = Integer(ARGV[1])
  else
    die
  end
rescue ArgumentError
  die
end

factors = min_factor..max_factor
width = max_product_width(factors)

factors.each do |x|
  factors.each { |y| printf ' %*d', width, x * y }
  puts
end
