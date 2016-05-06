import random

#SUM OF WEIGHTS OVER CAP

for j in xrange(10):
  k = (j+1)*10
  file = open(str(k)+'overcap.txt', 'w')

  sack = []
  for i in xrange(k):
    sack.append((random.randint(1,10),random.randint(10,100)))

  file.write(str(len(sack)) + "," + str(random.randint(2*k, 6*k)) + "\n")
  for item in sack:
    file.write(str(item[0]) + "," + str(item[1]) + "\n")

  file.close()

#SUM OF WEIGHTS UNDER CAP

for j in xrange(10):
  k = (j+1)*10
  file = open(str(k)+'undercap.txt', 'w')

  sack = []
  for i in xrange(k):
    sack.append((random.randint(1,10),random.randint(10,100)))

  file.write(str(len(sack)) + "," + str(len(sack)*10) + "\n")
  for item in sack:
    file.write(str(item[0]) + "," + str(item[1]) + "\n")
