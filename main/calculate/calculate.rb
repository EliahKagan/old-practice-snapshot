def add(*addends)
  addends.reduce(0, :+)
end

def subtract(minuend, *subtrahends)
  minuend - add(*subtrahends)
end

def calculate(*terms, fn_or_arg)
  if fn_or_arg.is_a?(Hash)
    method(fn_or_arg.keys.detect { |oper| fn_or_arg[oper] }).call(*terms)
  else
    add(*terms, fn_or_arg)
  end
end
