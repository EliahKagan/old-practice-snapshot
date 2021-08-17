def add(*a)
  a.reduce(0, :+)
end

def subtract(*a)
  a.reduce(:-)
end

def calculate(*args)
  a = []
  subtracting = false

  args.each do |x|
    if x.is_a?(Hash)
      subtracting ||= x[:subtract]
    else
      a << x
    end
  end

  subtracting ? subtract(*a) : add(*a)
end
