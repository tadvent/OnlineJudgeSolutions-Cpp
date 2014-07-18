/*
ID: wjl1241
PROG: numtri
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;

int main(){
    ifstream fin("numtri.in");
    ofstream fout("numtri.out");
    int n;
    vector<int> lastlevel;
    vector<int> thislevel;
    vector<int> newlevel;
    fin>>n;
    lastlevel.resize(n,0);
    thislevel.resize(n,0);
    newlevel.resize(n,0);

    for(int i=0;i<n;++i){
        for(int j=0;j<i+1;++j)fin>>newlevel[j];
        thislevel[0]=lastlevel[0]+newlevel[0];
        for(int j=1;j<i+1;++j)
            thislevel[j]=max(lastlevel[j-1],lastlevel[j])+newlevel[j];
        lastlevel.swap(thislevel);
    }

    int maxnum=lastlevel[0];
    for(int i=1;i<n;++i)
        if(lastlevel[i]>maxnum)maxnum=lastlevel[i];
    fout<<maxnum<<endl;
    return 0;
}