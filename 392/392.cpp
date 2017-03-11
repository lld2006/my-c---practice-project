#include <cstdio>
#include <vector>
#include <cmath>
#include "../lib/tools.h"
using namespace std;
extern "C"
{
    void dgetrf_(int* M, int* N, double* A, int* LDA, int* IPIV, int* INFO);
    void dgetrs_(char* TRANS, int* N, int* NRHS, double* A, int* LDA, int* IPIV, double* B, int* LDB, int* INFO);
}
int limit = 200;
double dg1(double theta1, double theta2)
{
    return sin(theta1) * cos(theta2);
}
double dg2(double theta1, double theta2)
{
    return sin(theta2)*(cos(theta1)-1);
}
double dh1(double theta1, double theta2)
{
    return sin(theta1)*(1-4*cos(theta1)) + sin(theta2)*cos(theta1);
}

double dh2(double theta1, double theta2)
{
    return cos(theta2)*sin(theta1);
}

double g(double theta1, double theta2)
{
    return cos(theta2) * (1.0-cos(theta1)); 
}

double h(double theta1, double theta2)
{
    return (sin(theta2) - sin(theta1)) * sin(theta1) - cos(theta1)*(1-cos(theta1));
}

void stamp_matrix(vector<double>& matrix, const vector<double>& vtheta){

    //first row and last row are special.
    //first line
    double v1 =dg1(vtheta[0], vtheta[1]) + dh1(vtheta[1], vtheta[2]);
    double v2 =dh2(vtheta[1], vtheta[2]);
    matrix[index0(limit, 0, 0)] = v1;
    matrix[index0(limit, 0, 1)] = v2;
    //middle lines
    for( int i = 1; i < limit-1; ++i){
        double v1 = dg1(vtheta[i], vtheta[i+1]);
        double v2 = dg2(vtheta[i], vtheta[i+1]) + dh1(vtheta[i+1], vtheta[i+2]);
        double v3 = dh2(vtheta[i+1], vtheta[i+2]);
        matrix[index0(limit, i, i-1)] = v1;
        matrix[index0(limit, i, i)] = v2;
        matrix[index0(limit, i, i+1)] = v3;
    }
    //last line
    v1 = dg1(vtheta[limit-1], vtheta[limit]);
    v2 = dg2(vtheta[limit-1], vtheta[limit]) + dh1(vtheta[limit], vtheta[limit+1]);
    matrix[index0(limit, limit-1, limit-2)] = v1;
    matrix[index0(limit, limit-1, limit-1)] = v2;
}

int main()
{
    double PI = atan(1.0)*4;
    vector<double> vtheta, dtheta;
    vtheta.resize(limit+2);
    dtheta.resize(limit);
    vtheta[0] = 0;
    vtheta[limit+1] = PI/2;
    for( int i = 1; i <= limit; ++i)
        vtheta[i] = (double) i /(limit+1)*PI/2;
    vector<double> matrix;
    matrix.resize(limit*limit, 0.0);
    while(true){
        stamp_matrix(matrix, vtheta);
        int dim = limit;
        vector<int> ipiv;
        ipiv.resize(dim, 0);
        int info = 0;
        dgetrf_(&dim, &dim, &matrix[0], &dim, &ipiv[0], &info);
        assert(info==0);
        char trans='T';
        int nrhs = 1;
        dtheta.clear();
        dtheta.resize(limit, 0);
        
        
        for(unsigned int i = 0; i < limit; ++i){
            dtheta[i] = -(g(vtheta[i], vtheta[i+1]) + h(vtheta[i+1], vtheta[i+2]));
        }
        dgetrs_(&trans, &dim, &nrhs, &matrix[0], &dim, &ipiv[0], &dtheta[0], &dim, &info);
        assert(info==0);
        double d2 = 0;
        for(unsigned int i = 0; i < dtheta.size(); ++i){
            d2 += dtheta[i] * dtheta[i];
            vtheta[i+1] += dtheta[i];
        }
        d2 = sqrt(d2);
        printf("d2 = %20.10f\n", d2);
        if(d2 < 1e-11)break;
    }
    double ret = 0;
    for( int i = 1; i<=limit; ++i){
        ret += (sin(vtheta[i+1]) - sin(vtheta[i]))*(1.0-cos(vtheta[i]));
    }
    printf("%20.10f\n", 4.0*(1.0-ret));
}
