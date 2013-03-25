//this code does not solve the problem. The correct way to solve this problem
//is to use recursion and complex<int> in c++ which is very convenient for this
//problem. we can find d_na d_nb very easily for any n up to 50. we need 
//to store the following informations, displacement relative to current 
//direction, and direction change after the operation relative to the initial
//direction, and number of step moves. then we can use some sort of bisection
//method to search for the nth step.
enum DIRECTION{NA=-1, PY=0, PX=1, NY=2, NX=3};
class dragon
{
  public:
    dragon():rv(0, 0), step(0), rot(1, 0){}
    dragon(complex<int> ci, i64 stepi, complex<int> ri):rv(ci)
                            , step(stepi)
                            , rot(ri)
    {}
    complex<int> rv;
    i64 step;
    complex<int> pre_rot;
    complex<int> post_rot;
    //"a" → "aRbFR"
    //"b" → "LFaLb"
};
void create_next_dragon(int ith, vector<dragon>& va, vector<dragon>& vb)
{
    assert(i>0);
    va[i] = va[i-1];
    complex<int> dir0(1,0), dir1(0, 1), dir2(-1, 0), dir3(0,-1);

    va[i].type = i;
    va[i].rot = va[i-1].rot*dir3;
    va[i].rv = va[i-1].rv + va[i].rot * vb[i-1].rv; 
    va[i].rot *= vb[i-1].rot;
    va[i].rv += va[i].rot;
    va[i].rot *= dir3;
    va[i].step+= vb[i-1].step+1;


}
int main()
{
    vector<dragon> vda, vdb;
    vda.resize(50);
    vdb.resize(50);
    vda[0].dset(0, 1, 1, 0, PY);
    vdb[0].dset(0, 0, 0, 0, PY);//let us first say no direction available for b0
    //should never use it
    for(unsigned int i = 1; i< vda.size(); ++i){
        create_next_dragon(i, vda, vdb);
    }
}
