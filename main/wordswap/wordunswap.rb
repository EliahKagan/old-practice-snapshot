#!/usr/bin/env ruby
$VERBOSE = true

require_relative 'wordlist'

# Print each idea out with the words fixed
Dir['idea-*.txt'].each do |name|
  idea = File.read(name)
  CODE_WORDS.each { |k, v| idea.gsub!(v, k) }
  puts idea
end
