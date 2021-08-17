# @return subscore, after-end index
def evaluate(parens, start)
  score = 0

  while parens[start] == '('
    subscore, start = evaluate(parens, start + 1)
    score += subscore
  end

  [(score.zero? ? 1 : score * 2), start + 1]
end

# @param {String} s
# @return {Integer}
def score_of_parentheses(s)
  score, = evaluate(s, 0)
  score / 2
end
