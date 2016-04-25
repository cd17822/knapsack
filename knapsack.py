import random

#SMALL

file = open('small_knapsack.txt', 'w')

sack = []
for i in xrange(5):
  sack.append((random.randint(1,10),random.randint(10,100)))

file.write(str(len(sack)) + "," + str(random.randint(10, 30)) + "\n")
for item in sack:
  file.write(str(item[0]) + "," + str(item[1]) + "\n")

file.close()

#MEDIUM

file = open('medium_knapsack.txt', 'w')

sack = []
for i in xrange(20):
  sack.append((random.randint(1,10),random.randint(10,100)))

file.write(str(len(sack)) + "," + str(random.randint(40, 120)) + "\n")
for item in sack:
  file.write(str(item[0]) + "," + str(item[1]) + "\n")

file.close()

#LARGE

file = open('large_knapsack.txt', 'w')

sack = []
for i in xrange(100):
  sack.append((random.randint(1,10),random.randint(10,100)))

file.write(str(len(sack)) + "," + str(random.randint(200, 600)) + "\n")
for item in sack:
  file.write(str(item[0]) + "," + str(item[1]) + "\n")

file.close()
