def apply(operator, arg1, arg2)
  case operator
  when '+' then arg1 + arg2
  when '-' then arg1 - arg2
  when '*' then arg1 * arg2
  when '/' then (arg1.to_f / arg2.to_f).to_i # round toward zero
  else raise ArgumentError, 'unrecognized operator'
  end
end

# @param {String[]} tokens
# @return {Integer}
def eval_rpn(tokens)
  stack = []

  tokens.each do |tok|
    if tok =~ /\A-?\d+\z/ # an integer
      stack.push(tok.to_i)
    else
      arg2 = stack.pop
      arg1 = stack.pop
      stack.push(apply(tok, arg1, arg2))
    end
  end

  raise ArgumentError, 'too few operators' if stack.length != 1
  stack.pop
end
