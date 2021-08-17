#!/usr/bin/env ruby
$VERBOSE = true

require_relative 'wordlist'

# Get evil idea and swap in code words
print 'Enter your new idea: '
idea = gets
CODE_WORDS.each { |k, v| idea.gsub!(k, v) }

# Save the jibberish to a new file
print 'Message encoded. Please enter a name for this idea: '
name = gets.strip
File.open("idea-#{name}.txt", 'w') { |f| f << idea }
