import pdb
def combination(n, r):
    #pdb.set_trace()
    if(n< 2* r):
        r = n- r;
    if(r == 0):
        return 1;
    prod = n;
    for x in range(2, r+1):
        prod *= (n+1-x);
        prod /=x;
    return prod;

n = 10000
m = 1000
p = 4 
nmod = 999999937;
nmod = 23
sum = 0;
s = 1;
for k in range(p,m, 1):
    v1 = combination(n, k)%nmod
    v2 = combination(k, p)%nmod
    value = (v1 * v2)%nmod;
    sum += value* s;
    s = -s;
    sum %= nmod;
    print(k,v1, v2, value, sum)
