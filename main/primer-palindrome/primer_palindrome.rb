def palindrome?(sentence)
  sentence = sentence.downcase.split.join
  sentence == sentence.reverse
end
