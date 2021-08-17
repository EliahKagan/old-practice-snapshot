def char_freq_map(str)
  # letter in str -> how many times it appears in str
  charfreqs = Hash.new(0)
  str.split('').each { |char| charfreqs[char] += 1 }

  charfreqs
end

def freq_freq_map(str)
  # number of times -> number of distinct letters appearing that often
  freqfreqs = Hash.new(0)
  char_freq_map(str).values.each { |freq| freqfreqs[freq] += 1 }

  freqfreqs
end

# def almost_uniform?

def valid?(str)
  freqfreqs = freq_freq_map(str)

  # 0 or 1 frequencies: valid; more than 2 frequences: invalid
  freqcount = freqfreqs.count
  return freqcount < 2 unless freqcount == 2

  # if we just have to remove 1 occurrence of 1 letter: valid
  return true if freqfreqs[1] == 1

  # if one letter appears one time more often than each other letter,
  # then a single occurrence of that more frequent letter may be removed
  # so all letters appear equally frequently -- such a string is valid
  freqs = freqfreqs.keys
  freqs_max = freqs.max
  freqs_max - freqs.min == 1 && freqfreqs[freqs_max] == 1
end

puts valid?(gets.chomp) ? 'YES' : 'NO'
