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
    int MC[dim];//col vec
    FILE* pFile = fopen("matrix.txt", "r");
    for(int i = 0; i < dim; ++i ){
        for(int j = 0; j < dim; ++j){
            fscanf(pFile, "%d", &M[i][j]);
        }
    }
    fclose(pFile);
    //initialize the first row and col

    for(int diag = 1; diag < dim ; ++diag){// this si actually col
        //initially update the col vector
        for(int i = 0; i < dim; ++i){
            MC[i] = M[i][diag-1] + M[i][diag];
        }

        for(int row = 0; row< dim; ++row){
            for(int rowa= row-1; rowa>=0; --rowa){
                if(MC[rowa] > MC[rowa+1]+M[rowa][diag]){
                    MC[rowa] = MC[rowa+1] + M[rowa][diag];
                }else{
                    break;
                }
            }
            for(int rowa= row+1; rowa < dim; ++rowa){
                if(MC[rowa] > MC[rowa-1]+M[rowa][diag]){
                    MC[rowa] = MC[rowa-1] + M[rowa][diag];
                }else{
                    break;
                }
            }
        }
        //update
        for(int row = 0; row < dim; ++row){
            M[row][diag] = MC[row];
        }
    }
    int dmin = 1000000;
    for(int row = 0; row < dim; ++row){
        if(MC[row]< dmin)
            dmin = MC[row];
    }
    printf("%d\n",dmin); 
}
