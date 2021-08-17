def location_in_hierarchy(object, method)
  hier = [object.class]

  while (sup = hier.last.superclass)
    hier << sup
  end

  hier.reverse!.find { |cls| cls.method_defined?(method) }
end
