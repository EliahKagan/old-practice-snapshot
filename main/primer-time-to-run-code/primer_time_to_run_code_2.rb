require 'benchmark'

def exec_time(code)
  Benchmark.measure { code.call }.real
end
