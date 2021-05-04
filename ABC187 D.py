n = int(input())

ts = []

A = 0
B = 0

for _ in range(n):
  a, b = map(int, input().split())

  A += a

  ts.append((2*a+b,a,b))

ts.sort(reverse=True)

ans = 0

for t in ts:
  (ci,ai,bi) = t

  A -= ai
  B += ai+bi

  ans += 1

  if A < B:
    break

print(ans)