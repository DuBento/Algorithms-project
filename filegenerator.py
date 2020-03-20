from random import randint
import os
# vals = [1, 5, 100, 1000, 10000, 100000, 200000, 300000, 400000, 500000, \
    # 600000, 700000, 800000, 900000, 1000000]
vals = []
for i in range(10000, 1000000, 2*10000):
    vals += [i]
    print(i)

for i in range(1000000, 100000001, 2*100000):
    vals += [i]
    print(i)

print("make of files")
for val in vals:
    #P = randint(randint(val//2, val), val)    #random value for V
    R = randint(randint(val//2, val), val)    #random value for V
    P = val    #random value for V
    # R = val - P         # E + V = value (constane growth)
    R = P         # E + V = value (constane growth)
    R = P        # V = E = value 
    rScc = randint(P, val)
    
    m = 1               #always the same
    M = P // rScc + randint(1, P)  # M * rScc > P
    seed = randint(0, 10)

    lst = [P, R, rScc, m, M, seed]
    lst = map(str, lst)
    lst = list(lst)
    print(str(val) + ":\t" + "\t".join(lst))
    lst = ["./gerador"] + lst
    lst.append( "> experimental/"+str(val) + ".in")
    os.system(" ".join(lst))
