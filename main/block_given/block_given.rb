def inflect(count, name)
  ret = "#{count} #{name}"
  ret << 's' if count != 1
  ret
end

def report(*args, **kwargs)
  reg = inflect(args.size, 'regular argument')
  kw = inflect(kwargs.size, 'keyword argument')
  desc = block_given? ? "#{reg}, #{kw}, and a block" : "#{reg} and #{kw}"
  puts "You passed #{desc}."
end
