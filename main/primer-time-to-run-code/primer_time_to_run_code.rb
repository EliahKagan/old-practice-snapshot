def exec_time(code)
  ti = Time.now
  code.call
  tf = Time.now

  tf - ti
end
