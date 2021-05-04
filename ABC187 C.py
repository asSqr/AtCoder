n = int(input())
strList = {}
result = "satisfiable"

for i in range(n):
  strList[input()] = True

for str in strList:
  if str[0] == "!":
    str = str[1:]
  else:
    str = "!" + str
  
  if str in strList:
    if str[0] == "!":
      result = str[1:]
    else:
      result = str
    break

print(result)