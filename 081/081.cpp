#include <cstdio>
using namespace std;
int min(int a, int b)
{
    return a<b ? a:b;
}
int main()
{
    int dim = 80;
    int M[dim][dim];
    FILE* pFile = fopen("matrix.txt", "r");
    for(int i = 0; i < dim; ++i ){
        for(int j = 0; j < dim; ++j){
            fscanf(pFile, "%d", &M[i][j]);
        }
    }
    fclose(pFile);
    //initialize the first row and col
    for(int col = 1; col < dim; ++col){
        M[0][col] += M[0][col-1];
        M[col][0] += M[col-1][0];
    }

    for(int diag = 1; diag < dim; ++diag){
        M[diag][diag] += min(M[diag][diag-1], M[diag-1][diag]);
        for(int col = diag+1; col < dim; ++col){
            M[diag][col] += min(M[diag][col-1], M[diag-1][col]);
            M[col][diag] += min(M[col-1][diag], M[col][diag-1]);
        }
    }
    printf("%d\n", M[dim-1][dim-1]);
}
