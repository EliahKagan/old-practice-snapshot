#!/usr/bin/env ruby

def fib_modified(a, b, n)
    (n - 2).times { a, b = b, a + b**2 }
    b
end

def read_record()
    gets.split.map(&:to_i)
end

puts fib_modified(*read_record)
