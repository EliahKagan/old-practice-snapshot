def xyz_there(s):
  e = 'xyz'
  if s.startswith(e):
    return True
  
  n = len(s)
  i = 0
  while i != n:
    i += 1
    i = s.find(e, i)
    if i == -1:
      break
    if s[i - 1] != '.':
      return True
  
  return False
    
