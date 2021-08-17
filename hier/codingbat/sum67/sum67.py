Q = 6
E = 7

def sum67(nums):
  skip = False
  acc = 0

  for x in nums:
    if skip:
      if x == E:
        skip = False
    else:
      if x == Q:
        skip = True
      else:
        acc += x

  return acc
