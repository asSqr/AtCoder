n = int(input())
citizen = {}
cities = 0
aoki = 0
takahashi = 0
for i in range(n):
  x, y = map(int, input().split())
  citizen.setdefault((i,x,y), x * 2 + y) 
  aoki += x

citizen = sorted(citizen.items(), key=lambda x: x[1], reverse=True)

for (city,ai,bi), value in citizen:
  takahashi += ai+bi
  aoki -= ai
  cities += 1

  if aoki < takahashi:
    break

print(cities)