#!/usr/bin/env ruby
$VERBOSE = true

def wipe_mutterings_from(sentence)
  while sentence.gsub!(/\([^(]*?\)/, ''); end
end

what_he_said = <<~UTTERANCE
  But, strangely (em-pithy-dah),
  I learned upon, played upon (pon-shoo) the
  organs on my home (oth-rea) planet."
UTTERANCE

wipe_mutterings_from(what_he_said)
puts what_he_said
