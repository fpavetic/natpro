import string
import sys

inputs = []
for line in sys.stdin:
  inputs.append(line)

def get_next(s):
  assert len(s) > 0
  l = [x for x in s]
#  print l
  if l.count('9') == len(l):
    s = "1"
    for i in xrange(len(l)-1):
      s += "0"
    s += "1"
    return s
  else:
    i = 0
    mid = len(l)/2
#    print len(l), mid
    has_to_increase = False
    while i <= mid:
      if l[i] >= l[-i-1]:
        has_to_increase = False
        l[-i-1] = l[i]
        i += 1
      else:
        has_to_increase = True
        l[-i-1] = l[i]
        i += 1
    if "".join(l) <= s:
      has_to_increase = True

    if has_to_increase:
      for j in xrange(mid, -1, -1):
        if l[j] != '9' or l[-j-1] != '9':
          nullify_range = False
          if l[j] > l[-j-1]:
            l[-j-1] = l[j]
          elif l[j] < l[-j-1]:
            l[j] = l[-j-1]
            nullify_range = True
          else:
            l[j] = chr(ord(l[j])+1)
            if j != len(l) - j - 1:
              l[-j-1] = chr(ord(l[-j-1])+1)
            nullify_range = True
          if nullify_range:
            for i in xrange(j+1, len(l)-j-1):
              l[i] = '0'
          break
    return "".join(l)

def is_palindrom(s):
  for i in xrange(0, len(s)):
    if s[i] != s[-i-1]:
      return False
  return True

inputs = inputs[1:]

for s in inputs:
  while len(s) > 1 and s[0] == '0':
    s = s[1:]
  s = s.rstrip('\n')
  print get_next(s)

#for i in xrange(1, 100000):
#  j = i+1
#  next_palindrom = get_next(str(i))
#  print i, next_palindrom
#  while True:
#    if is_palindrom(str(j)):
#      if str(j) != next_palindrom:
#        print str(j)
#        sys.exit(1)
#      break
#    j += 1
