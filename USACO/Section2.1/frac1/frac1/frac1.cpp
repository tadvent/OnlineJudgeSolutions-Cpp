/*
ID: wjl1241
PROG: frac1
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;

const float eps=0.00001;
const int N=160;
int fenzi[N+1];
vector<int> minfenmu;

int findmin(const int n, int &above, int &below);

int main(){
    ifstream fin("frac1.in");
    ofstream fout("frac1.out");
    for(int i=0;i<N+1;++i)fenzi[i]=0;

    int n,above,below;
    fin>>n;
    minfenmu.reserve(n);

    while(!findmin(n,above,below)){
        fout<<above<<'/'<<below<<'\n';
    }
    fout<<"1/1"<<endl;
    return 0;
}

int findmin(const int n, int &above, int &below){
    //if the next frac is 1, then return 1; else return 0
    //to restore the min frac's fenmus

    float min=1.1,tmp;
    for(int i=1;i<n+1;++i){
        if(min-(tmp=float(fenzi[i])/i)>eps){
            min=tmp;
            minfenmu.clear();
            minfenmu.push_back(i);
        }
        else if(min-tmp<eps && tmp-min<eps){
            minfenmu.push_back(i);
        }
    }
    below=minfenmu.front();
    above=fenzi[below];
    for(int i=0;i<(int)minfenmu.size();++i)++fenzi[minfenmu[i]];

    if(min-1.0<eps && 1.0-min<eps)return 1;
    return 0;
}