tot = 0;
for n in range(1, 1001):
    tot = tot + pow(n, n, 10000000000);    
print tot%10000000000;
