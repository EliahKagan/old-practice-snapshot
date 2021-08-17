#!/usr/bin/env ruby
$VERBOSE = true

# A module to include in classes.
module Foo
  def self.g
    puts 'Foo.g'
  end

  def f
    puts 'Foo#f'
  end
end

# A class that includes a module.
class Bar
  include Foo
end

Bar.new.f

x = Object.new
x.extend(Foo)
x.f

# A class that starts out empty...
class Baz
end

Baz.extend(Foo)
Baz.f
