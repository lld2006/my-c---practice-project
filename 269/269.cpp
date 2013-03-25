typedef map<vector<int>, i64> solmap;
//this is a dynamic programming + inclusion exclusion problem. 
//it is not difficult but need some time to coding
void create_vec(vector<int>& cands, int num)
{
    cands.push_back(1);
    for(int i = 2; i<= num; ++i){
        if(num % i == 0)
            cands.push_back(i);
    }
}
int main()
{
    int nmax = 10000000000000000LL;
    i64 sum = nmax/10;
    vector<int> cands;
    i64 total = 0;
    
    for(unsigned int i = 1; i < 9; ++i){
        solmap smap;
        create_vec(cands, i);
        vector<int> vn;
        vn.resize(cands.size(), i);
        smap.insert(make_pair(vn, 1LL));
        search_for_solution(smap);
    }
}
