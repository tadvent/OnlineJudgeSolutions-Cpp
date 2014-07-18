/*
ID: wjl1241
PROG: ariprog
LANG: C++
*/

#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

const int maxm=250;
const int maxn=25;
int n,m,maxstep,maxstart;

class Ans {
public:
    int start;
    int step;
    Ans(int _start, int _step):start(_start),step(_step){}
    bool operator<(const Ans &r)const{
        return step<r.step;
        //if(step<r.step)return true;
        //if(step>r.step)return false;
        //return start<r.start;
    }
};

bool check(int start,const int step,const vector<int> &bisqure,const int n){
    for(int i=0;i<n;++i){
        if(start>maxstart)return false;
        if(!bisqure[start])return false;
        start+=step;
    }
    return true;
}

int main(){
    ifstream fin("ariprog.in");
    ofstream fout("ariprog.out");
    vector<int> squre(maxm+1);
    vector<int> bisqure(maxm*maxm*2+1,0);

    fin>>n>>m;

    for(int i=0;i<=m;++i)squre[i]=i*i;
    for(int i=0;i<=m;++i)for(int j=0;j<=m;++j)
        bisqure[squre[i]+squre[j]]=1;
    maxstart=m*m*2;
    maxstep=squre[m]*2/(n-1);

    vector<Ans> ans;
    bool nout=true;
    for(int start=0;start<maxstart;++start)if(bisqure[start])
        for(int step=1;step<=maxstep && start+step<maxstart;++step)
            if(bisqure[start+step])if(check(start+step*2,step,bisqure,n-2)){
                ans.push_back(Ans(start,step));
                if(nout)nout=false;
            }

    sort(ans.begin(),ans.end());
    for(size_t i=0;i<ans.size();++i)
        fout<<ans[i].start<<' '<<ans[i].step<<'\n';
    if(nout)fout<<"NONE"<<endl;

    return 0;
}