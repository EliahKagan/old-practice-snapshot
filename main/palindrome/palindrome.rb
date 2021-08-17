def palindrome?(sentence)
  sentence = sentence.split.join.upcase!
  sentence == sentence.reverse
end
