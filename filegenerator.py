from random import randint
vals = [1, 5, 100, 1000, 10000, 100000, 200000, 300000, 400000, 500000, \
    600000, 700000, 800000, 900000, 1000000]

for val in vals:
    P = randint(val-randint(0,val//2), val)    #random value for V
    R = val - P         # E + V = value (constane growth)
    rScc = randint(1, val)
    while rScc > P:
        rScc = randint(1, val) #random num SCCs
    
    m = 1               #always the same
    M = P // rScc + randint(1, P)  # M * rScc > P
    seed = randint(0, 10)

    print(P, R, rScc, m, M, seed, sep="\t")