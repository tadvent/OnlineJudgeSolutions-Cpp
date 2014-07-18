/*
ID: wjl1241
PROG: milk3
LANG: C++
*/

#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

int bsize[3];
bool state[21][21][21];
vector<int> ans;

bool pour(const int id1, const int id2, vector<int> &bnow){
    if(bnow[id1]==0)return false;
    if(bnow[id2]==bsize[id2])return false;
    int pourout=min(bnow[id1],bsize[id2]-bnow[id2]);
    bnow[id1]-=pourout;
    bnow[id2]+=pourout;
    if(state[bnow[0]][bnow[1]][bnow[2]]){
        bnow[id1]+=pourout;
        bnow[id2]-=pourout;
        return false;
    }
    return true;
}

void check(const vector<int> &bnow){
    if(bnow[0]==0){
        if(find(ans.begin(),ans.end(),bnow[2])==ans.end())
            ans.push_back(bnow[2]);
    }
}

void search(int inid1, int inid2, vector<int> bnow){
    check(bnow);
    state[bnow[0]][bnow[1]][bnow[2]]=true;
    for(int i=0;i<3;++i)for(int j=0;j<3;++j){
        if(i==j)continue;
        if(i==inid2&&j==inid1)continue;
        if(pour(i,j,bnow))search(i,j,bnow);
    }
}

int main(){
    ifstream fin("milk3.in");
    ofstream fout("milk3.out");
    vector<int> bnow(3);

    for(int i=0;i<3;++i)fin>>bsize[i];
    bnow[0]=bnow[1]=0;
    bnow[2]=bsize[2];
    for(int i=0;i<21;++i)for(int j=0;j<21;++j)for(int k=0;k<21;++k)
        state[i][j][k]=false;

    search(0,0,bnow);
    sort(ans.begin(),ans.end());

    fout<<ans[0];
    for(size_t i=1;i<ans.size();++i)fout<<' '<<ans[i];
    fout<<endl;

    return 0;
}