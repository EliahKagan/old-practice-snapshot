class Object
  def superclasses
    ret = []
    cls = self
    ret << cls while (cls = cls.superclass)
    ret
  end
end

class Bar
end

class Foo < Bar
end

p Foo.superclasses  # should be [Bar, Object, BasicObject]
