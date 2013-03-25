#include <vector>
#include <cassert>
#include <cstdio>
using namespace std;
extern "C"
{
    void dgetrf_(int* M, int* N, double* A, int* LDA, int* IPIV, int* INFO);
    void dgetrs_(char* TRANS, int* N, int* NRHS, double* A, int* LDA, int* IPIV, double* B, int* LDB, int* INFO);
}
int xdim = 5;
int dim = xdim*xdim;
vector<vector<int>> neighbors;
double prob_to_target(int target, const vector<int>& fvec, int startp )
{
    vector<double> mat;
    vector<double> rhs;
    mat.clear();rhs.clear();
    mat.resize(dim*dim, 0.0);
    rhs.resize(dim, 0.0); // all probability set to zero initially

    for( int i = 0; i < dim; ++i){
        if(fvec[i]){
            mat[dim*i+i] = 1.0;
            continue;
        }
        if(i==target){
            mat[i*dim+i] = 1.0;
            rhs[i] = 1.0;
            continue;
        }
        int nn = neighbors[i].size();
        assert(nn > 0);
        double p = 1.0/nn;
        
        mat[dim*i+i] = 1.0;
        for(unsigned int j = 0; j < neighbors[i].size(); ++j){
            int nx = neighbors[i][j];
            mat[dim*i+nx] = -p;
        }
    }
    int info=0;
    vector<int> ipiv;
    ipiv.resize(dim, 0);
    dgetrf_(&dim, &dim, &mat[0], &dim, &ipiv[0], &info);
    assert(info==0);
    char trans='T';
    int nrhs = 1;
    dgetrs_(&trans, &dim, &nrhs, &mat[0], &dim, &ipiv[0], &rhs[0], &dim, &info);
    assert(info==0);
    return rhs[startp];
}


double steps_to_target(int target, const vector<int>& fvec, int startp)
{
    vector<double> mat;
    vector<double> rhs;
    mat.clear();rhs.clear();
    mat.resize(dim*dim, 0.0);
    rhs.resize(dim, 0.0);
    
    for( int i = 0; i < dim; ++i){
        if(fvec[i] || target == i){
            mat[dim*i+i] = 1.0; //actually nobody can  have 
            //such branches, dummy equation
            continue;
        }
        
        mat[i*dim+i] = 1.0;
        int nn = neighbors[i].size();
        assert(nn > 0);
        double p = 1.0/nn;
        for(unsigned int j = 0; j < neighbors[i].size(); ++j){
            int nx = neighbors[i][j];
            if(fvec[nx])
                continue;
            assert(nx != i);
            mat[i*dim+nx] = -p;
            rhs[i] = 1.0;
        }
    }
    int info=0;
    vector<int> ipiv;
    ipiv.resize(dim, 0);
    dgetrf_(&dim, &dim, &mat[0], &dim, &ipiv[0], &info);
    assert(info==0);
    char trans='T';
    int nrhs = 1;
    dgetrs_(&trans, &dim, &nrhs, &mat[0], &dim, &ipiv[0], &rhs[0], &dim, &info);
    assert(info==0);
    return rhs[startp];
}

//vlow and vhigh are visited or put it in another way seed has been moved
//nlow and nhigh are bitset 
//dir == 0, low to high 
//dir == 1 high to low;
double expectation_from_config(int nlow, int nhigh, int cpos) 
{

    //just moved a new seed to top
    if(nhigh == (1<<xdim)-1)
        return 0.0;

    //current at top need to check bottom
    double steps = 0.0;
    if(cpos >= dim-xdim){
        //TO LOW
        // check low forbidden target is 
        // also set as forbidden at first
        vector<int> fvec;
        fvec.resize(xdim, 1);
        fvec.resize(dim, 0); //not visited
        int n0 = 1;
        for( int i = 0; i < xdim; ++i){
            if(nlow & n0)
                fvec[i] = 0;
            n0 <<= 1;
        }

        for( int i = 0; i< xdim; ++i){
            if(nlow & (1<<i)) 
                continue;
            int target  = i;
            fvec[i] = 0;
            double px = prob_to_target(target, fvec, cpos);
            double dx = steps_to_target(target, fvec, cpos);
            int nlow1 = nlow + (1<<i);
            steps += px*(dx + expectation_from_config(nlow1, nhigh, target));
            //set back fvec, otherwise messed up
            fvec[i] = 1;
        }
    }else{
        //TO HIGH
        assert(cpos <= 4);
        vector<int> fvec;
        fvec.resize(dim-xdim, 0);
        fvec.resize(dim, 1);//20--24 are now forbidden
        int n0 = 1;
        for( int i = 0; i < xdim; ++i){
            if(nhigh & (1<<i))
                fvec[i+dim-xdim] = 0;//i has been visited, so no restriction
            n0 <<= 1;
        }
        for( int i = 0; i <xdim; ++i){
            if(nhigh & (1<<i))
                continue;
            int target = i + dim-xdim;
            fvec[target] = 0;
            double px = prob_to_target(target, fvec, cpos);
            double dx = steps_to_target(target, fvec, cpos);
            int nhigh1 = nhigh + (1<<i);
            //printf("start=%d dest %d nlow=%d nhigh=%d %f %f\n", cpos, target,nlow, nhigh1, px, dx);
            steps += px*(dx+expectation_from_config(nlow, nhigh1, target));
            fvec[target] = 1;
        }
    }
    return steps;
}

//5*5 is modeled by 0 --- 24;
int main()
{
    //first create all neighbors for each grid;
    neighbors.resize(dim);
    for( int i = 0; i < dim; ++i){
        int row = i/xdim;
        int col = i%xdim;
        if(row > 0 && row < xdim-1){
            neighbors[i].push_back(i-xdim);
            neighbors[i].push_back(i+xdim);
        }else if(row == 0){
            neighbors[i].push_back(i+xdim);
        }else{
            neighbors[i].push_back(i-xdim);
        }
        if(col > 0 && col < xdim-1){
            neighbors[i].push_back(i-1);
            neighbors[i].push_back(i+1);
        }else if(col==0){
            neighbors[i].push_back(i+1);
        }else{
            neighbors[i].push_back(i-1);
        }
    }
    //now it is time to find expected steps for this problem
    int start = (dim-1)/2;
    vector<int> fvec;
    fvec.resize(xdim, 1);
    fvec.resize(dim,0);
    double total_steps = 0.0;
    int nhigh = 0;
    //for( int i = 0; i < xdim; ++i){
    //dirty speed up
    for( int i = 0; i < 3; ++i){
        fvec[i] = 0;
        double pi = prob_to_target(i, fvec, start);
        double di = steps_to_target(i, fvec, start);
        int nlow1 = (1<<i);
        double dj = expectation_from_config(nlow1, nhigh,i);
        //printf("start=%d prob=%f dinit=%f nlow=%d nhigh=%d dj=%f\n", i, pi, di, nlow1, nhigh, dj);
        double factor = 2.0;
        if(i == 2) factor = 1.0; 
        total_steps +=factor* pi * (di + dj);
        fvec[i] = 1;
    }
    printf("%25.15f\n", total_steps);
}
