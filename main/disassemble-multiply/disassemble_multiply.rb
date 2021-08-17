#!/usr/bin/env ruby
$VERBOSE = true

def multiply(x, y)
  x * y
end

# See https://ruby-doc.org/core-2.2.3/RubyVM/InstructionSequence.html#method-c-disasm
print RubyVM::InstructionSequence.disasm(method(:multiply))
