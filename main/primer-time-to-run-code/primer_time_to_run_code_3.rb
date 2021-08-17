require 'benchmark'

def exec_time(code)
  Benchmark.realtime { code.call }
end
