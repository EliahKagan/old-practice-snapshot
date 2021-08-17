#!/usr/bin/env ruby
$VERBOSE = true

# A class that increments a counter each time an object is constructed.
class Counted
  @@count = 0

  def initialize
    @id = @@count
    @@count += 1
  end

  def to_s
    format '#<%<type>s:0x%<obj_id>x:%<my_id>d>',
           type: self.class, obj_id: object_id, my_id: @id
  end
end

x = Counted.new
y = Counted.new
z = Counted.new
[x, y, z].each { |obj| puts obj }
