def is_ancestor?(klass, subclass)
  while subclass do
    return true if subclass == klass
    subclass = subclass.superclass
  end
  false
end
