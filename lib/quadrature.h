struct Quadrature {
    int n;
    virtual double next() = 0;
};

template <class T> struct Trapzd : Quadrature {
    double a, b, s; //integrate from a to b sum to s
    T& func;
    Trapzd() {};
    Trapzd( T& funcc, const double aa, const double bb):
        func(funcc), a(aa), b(bb) {n=0;}
    double next(){
        double x, tnm, sum, del;
        int it=1, j;
        n++;
        if(n == 1)
            return(s = 0.5*(b-a)*(func(a)+func(b)));
        else{
            it <<= n-2;
            tnm = it;
            del = (b-a)/tnm;
            x = a + 0.5*del;
            for(sum = 0.0, j = 0; j < it; ++j, x += del) 
                sum += func(x);
            s  = 0.5*(s+(b-a)*sum/tnm);
            return s;
        }
    }
};

template<class T>
double qtrap(T &func, const double a, const double b const double eps = 1.e-10){
    const int JMAX = 20; //is it too small?
    double s, olds = 0.0;
    trapzd<T> t(func,a, b);
    for(int j = 0; j < JMAX; ++j){
        s = t.next();
        if(j > 5)
            if(abs(s-olds) < eps*abs(olds) || (s==0.0 && olds == 0.0))
                return s;
        olds = s;
    }
    //throw 
}

