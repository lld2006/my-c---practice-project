from sympy.solvers.diophantine import diop_DN
nmax = 1000000;
sum = 0;
for i in range(1, 500):
    print(i, sum)
    D = 4*i*i+1
    N = i*i
    sol = diop_DN(D, 1)
    print(i, sol)
    r = sol[0][0]
    s = sol[0][1]
    solFund = diop_DN(D, N) 

    for sf in solFund:
        p=sf[0]
        q=sf[1]
        while(p<nmax):
            sum +=p;
            (p, q) = (p*r+D*s*q, p*s+r*q) #p is area (q i)

print("sum=", sum)

