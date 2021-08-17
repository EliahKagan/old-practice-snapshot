def xyz_there(s):
  e = 'xyz'
  if s.startswith(e):
    return True
  
  n = len(s)
  i = 0
  while i not in (-1, n):
    i += 1
    i = s.find(e, i)
    if s[i - 1] != '.':
      return True
  
  return False
    
