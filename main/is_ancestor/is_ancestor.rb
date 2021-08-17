def is_ancestor?(klass, subclass) # demonstration without <, <=, >, or >=
  return false unless subclass
  (sup = subclass.superclass) == klass || is_ancestor?(klass, sup)
end
