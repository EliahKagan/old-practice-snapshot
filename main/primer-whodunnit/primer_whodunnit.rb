def location_in_hierarchy(object, method)
  hier = []

  cls = object.class
  while cls
    hier.unshift(cls)
    cls = cls.superclass
  end

  hier.find { |cls| cls.method_defined?(method) }
end
