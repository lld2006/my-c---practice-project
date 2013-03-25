int gid = 0;
map<int, int> cfg_idmap;
int find_in_vector(const vector<int>& vn, int num)
{
    for(unsigned int j = 0; j < vn.size(); ++j){
        if(vn[j] == num)
            return j;
    }
    return -1;
}
//number value still need to be updated
void update_L(vector<int>& vn, int num)
{
    int pos = -1;
    if((pos = find_in_vector(vn, num))==-1){
        if(vn.size() < 5){
            assert(vn.size()==num);
            vn.push_back(num);
        }else{ //remove the oldest number
            for(unsigned int i = 1; i < vn.size(); ++i){
                vn[i-1] = vn[i];
            }
            vn.back() = num;
        }
    }else{//found
        for(unsigned int i = pos+1; i < vn.size(); ++i){
            vn[i-1] = vn[i];
        }
        vn.back() = num; //back means recently used
    }
}
void getNewStates(const vector<int>& vl, vector<int>& vr)
{
    assert(vl.size() == vr.size());
    int nsize = vl.size();
    if(nsize < 5){
        //insert an existing number in R
        //R side has nothing to do;
        for(int i = 1; i <= nsize; ++i){
            vector<int> v1new(v1);
            update_L(v1, i);
        }
        //add one for R
        for(int i = nsize+1; i <= 10; ++i){

        }
    }
    vector<int> vn;
    vn.resize(11, 0);
    for(unsigned int i = 1; i < vr.size(); ++i)
        vn[i] = 1;
    
    for(unsigned int i = 0; i < vl.size(); ++i)
        vn[vl[i]] = 1;
    
    
}
int main()
{
    cfg_idmap.insert(make_pair(1, gid++));
}
