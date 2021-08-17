def sort_string(string)
  string.split.sort_by(&:length).join(' ')
end
