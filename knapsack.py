import random

#SMALL, SUM OF WEIGHTS OVER CAP

file = open('smallovercap.txt', 'w')

sack = []
for i in xrange(5):
  sack.append((random.randint(1,10),random.randint(10,100)))

file.write(str(len(sack)) + "," + str(random.randint(10, 30)) + "\n")
for item in sack:
  file.write(str(item[0]) + "," + str(item[1]) + "\n")

file.close()

#MEDIUM, SUM OF WEIGHTS OVER CAP

file = open('mediumovercap.txt', 'w')

sack = []
for i in xrange(15):
  sack.append((random.randint(1,10),random.randint(10,100)))

file.write(str(len(sack)) + "," + str(random.randint(30, 90)) + "\n")
for item in sack:
  file.write(str(item[0]) + "," + str(item[1]) + "\n")

file.close()

#LARGE, SUM OF WEIGHTS OVER CAP

file = open('largeovercap.txt', 'w')

sack = []
for i in xrange(25):
  sack.append((random.randint(1,10),random.randint(10,100)))

file.write(str(len(sack)) + "," + str(random.randint(50, 150)) + "\n")
for item in sack:
  file.write(str(item[0]) + "," + str(item[1]) + "\n")

file.close()

import random

#SMALL, SUM OF WEIGHTS UNDER CAP

file = open('smallundercap.txt', 'w')

sack = []
for i in xrange(5):
  sack.append((random.randint(1,10),random.randint(10,100)))

file.write(str(len(sack)) + "," + str(len(sack)*10) + "\n")
for item in sack:
  file.write(str(item[0]) + "," + str(item[1]) + "\n")

file.close()

#MEDIUM, SUM OF WEIGHTS UNDER CAP

file = open('mediumundercap.txt', 'w')

sack = []
for i in xrange(15):
  sack.append((random.randint(1,10),random.randint(10,100)))

file.write(str(len(sack)) + "," + str(len(sack)*10) + "\n")
for item in sack:
  file.write(str(item[0]) + "," + str(item[1]) + "\n")

file.close()

#LARGE, SUM OF WEIGHTS UNDER CAP

file = open('largeundercap.txt', 'w')

sack = []
for i in xrange(25):
  sack.append((random.randint(1,10),random.randint(10,100)))

file.write(str(len(sack)) + "," + str(len(sack)*10) + "\n")
for item in sack:
  file.write(str(item[0]) + "," + str(item[1]) + "\n")

file.close()

