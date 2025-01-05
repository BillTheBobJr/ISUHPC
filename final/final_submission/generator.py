import random
from collections import defaultdict

# You can use this script to generate a matrix in CSR format, along with a vector to multiply it by
# Size = number of non-zeros
# tx = number of columns
# ty = number of rows

size = 80000
tx = 2000
ty = 2000
allx = []
ally = []
val = []
loc = []
for i in range(size):
    x = random.randint(0, tx - 1)
    y = random.randint(0, ty - 1)
    s = str(x) + "," + str(y)
    if(not s in loc):
        loc.append(s)
        allx.append(x)
        ally.append(y)
        val.append(random.randint(1,9))
    else:
        i -= 1
x = []
for i in range(tx):
    x.append(random.randint(2,9))

final = {}
for i in range(tx):
    final[i] = {}
for i in range(len(val)):
    final[allx[i]][ally[i]] = val[i]


s1 = s2 = s3 = s4 = '{'

prev = 0
s1 += '0,'
for key in final.keys():
    kList = list(final[key].keys())
    prev += len(kList)
    s1 += str(prev) + ','
    kList.sort()
    for k in kList:
        s2 += str(k) + ','
        s3 += str(final[key][k]) + ','

for ele in x:
    s4 += str(ele) + ','


s1 = s1[:-1]
s2 = s2[:-1]
s3 = s3[:-1]
s4 = s4[:-1]
s1 += '}'
s2 += '}'
s3 += '}'
s4 += '}'

print(s1)  # row_ptr array
print(s2)  # col_idx array
print(s3)  # value array
print(s4)  # x array
    