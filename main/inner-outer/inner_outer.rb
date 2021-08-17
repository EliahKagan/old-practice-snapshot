#!/usr/bin/env ruby
$VERBOSE = true

A = 10

# A module with its own constant called A.
module Foo
  A = 20

  def self.inner_a
    A
  end

  def self.outer_a
    ::A
  end

  # A submodule, to demonstrate scoping from unary ::.
  module Bar
    def self.outermost_a
      ::A
    end
  end
end

puts Foo.inner_a, Foo.outer_a, Foo::Bar.outermost_a
