#!/usr/bin/env ruby
$VERBOSE = true

def santa
  raise 'ho ho ho'
end

def rudolf
  santa
rescue RuntimeError => e
  p e.backtrace
  raise e
end

def olive
  santa
rescue RuntimeError => e
  p e.backtrace
  raise
end

method(ARGV.first).call
