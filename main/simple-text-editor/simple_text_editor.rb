buffer = ''

def buffer.appender(text)
  -> { self << text } # lambda returns augmented string (which we'll discard)
end

def buffer.eraser(count) # would behave improperly for nonpositive count
  -> { slice!(-count..-1) } # lambda returns removed string (which we'll use)
end

undos = []

gets # ignore Q value; apparently it is unreliable

while (s = gets)
  a = s.chomp.split

  case a[0].to_i
  when 1 # append
    w = a[1]
    buffer.appender(w).call
    undos.push(buffer.eraser(w.length))

  when 2 # erase
    k = a[1].to_i
    w = buffer.eraser(k).call
    undos.push(buffer.appender(w))

  when 3 # get
    k = a[1].to_i - 1
    puts buffer[k]

  when 4 # undo
    undos.pop.call

  else
    abort 'invalid query type'
  end
end
