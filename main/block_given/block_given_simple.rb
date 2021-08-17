def report(*args)
  message = "You passed #{args.size} argument"
  message << 's' unless args.one?
  message << ' and a block' if block_given?
  message << '.'
  puts message
end
