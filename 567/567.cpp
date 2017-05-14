void create_new)pascal_triangle(vector<int64_t>& vold, vector<int64_t>& vnew)
{
    vnew.clear();
    vnew.resize(vold.size()+1);
    vnew[0] = 1;
    unsigned int i;
    for(i = 1; i< vold.size(); ++i){
        vnew[i] = vold[i] + vold[i-1];
    }
    vnew[i] = 1;
}
int main()
{
    
}
