import sys

def sum(x):
  if x < 0:
    return -sum(-x)
  return x * (x+1) / 2

def sum_range(a, b):
  if a > b:
    return sum_range(b, a)
  if a == 0:
    return sum(b)
  if b == 0:
    return sum(a)
  if a < 0 and b < 0:
    return -sum_range(-b, -a)
  if a > 0 and b > 0:
    return sum(b) - sum(a - 1)
  assert (a < 0 and b > 0)
  return sum(b) + sum(a)

for line in sys.stdin:
  (a, b) = line.split(" ")
  a = int(a)
  b = int(b)
  assert (a <= b)
  print sum_range(a, b)
