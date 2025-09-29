import random

f = open("test.txt", "r")
data = list(f)

map = {
    
}
for i1 in data:
    for i2 in i1:
        R[i2][1] += 1
        G[i2][1] += 1
        B[i2][1] += 1
        A[i2][1] += 1
        L[i2][1] += 1

R.sort(key=lambda x: x[1], reverse=True)
G.sort(key=lambda x: x[1], reverse=True)
B.sort(key=lambda x: x[1], reverse=True)
A.sort(key=lambda x: x[1], reverse=True)
L.sort(key=lambda x: x[1], reverse=True)

colormap = []
for i in R:
    colormap.append(i[1])
    


file = open("test2.txt", "r")
file.write()
