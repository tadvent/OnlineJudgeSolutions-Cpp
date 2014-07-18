/*
ID: wjl1241
PROG: agrinet
LANG: C++
*/

#include<fstream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

vector<vector<int> > arcs;
//const int infinite=1000000000;

struct arc{
    arc(int f,int t):from(f),to(t){}
    int from;
    int to;
    bool operator>(const arc &comp)const{
        return arcs[from][to]>arcs[comp.from][comp.to];
    }
};

int main(){
    ifstream fin("agrinet.in");
    ofstream fout("agrinet.out");
    int n;
    fin>>n;
    arcs.resize(n);
    for(int i=0;i<n;++i){
        arcs[i].resize(n);
        for(int j=0;j<n;++j){
            fin>>arcs[i][j];
        }
    }

    priority_queue<arc,vector<arc>,greater<arc> > pq;
    vector<bool> s(n,false);

    s[0]=true;
    int sn=1,totalcost=0;
    for(int i=0;i<n;++i)if(!s[i]){
        pq.push(arc(0,i));
    }
    while(sn<(int)s.size()){
        arc thearc=pq.top();
        pq.pop();
        if(s[thearc.to])continue;
        totalcost+=arcs[thearc.from][thearc.to];
        s[thearc.to]=true;
        ++sn;

        for(int i=0;i<n;++i)if(!s[i]){
            pq.push(arc(thearc.to,i));
        }
    }

    fout<<totalcost<<endl;

    return 0;
}