// no code for this problem, the idea is simple. 
// first notice that all qualified numbers must take the form
// n = p1*p2 *...*pn, so it is square free. also, p must be odd.
// then call q1=p1*p2*...*p_{n-1} and the corresponding totient function for 
// this number q2. then write the cosillience number in form of q1 and q2.
// try to find integer solutions, and check if the solution is prime.
// recursive method is used since 3 primes or more are possible. 
// performance is not good, need to learn and find better method.
// my run is about 80s.
