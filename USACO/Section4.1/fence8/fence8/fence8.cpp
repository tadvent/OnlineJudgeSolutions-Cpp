/*
ID: wjl1241
PROG: fence8
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
ifstream fin("fence8.in");
ofstream fout("fence8.out");

const int maxboard=50+1;
const int maxrail=1023+1;

int nboard,nrail,best;
vector<int> board(maxboard);
vector<int> rail(maxrail);
vector<int> remain(maxboard);
vector<int> sumlen(maxrail);
//vector<int> minindex(maxrail);
long long sum=0;
long long maywaste,waste;

void dfs(int r,int index1){
    if(r == 0){
        for(int i=index1; i<nboard; ++i)
            if (remain[i]>=rail[0]){
                fout << best+1 << endl;
                fout.close();
                exit(0);
            }
        return;
    }
    for(int i=index1; i<nboard; ++i)
        if(remain[i]>=rail[r]){
            long long oldwaste=waste;
            remain[i]-=rail[r];
            if (remain[i]<rail[0] && waste+remain[i]>maywaste){
                remain[i]+=rail[r];
                continue;
            }
            if (remain[i]<rail[0]) waste+=remain[i];
            if(rail[r-1] == rail[r]) dfs(r-1,i);
            else dfs(r-1,0);
            remain[i]+=rail[r];
            waste=oldwaste;
        }
}

int main(){
    fin>>nboard;
    for(int i=0;i<nboard;i++){
        fin>>board[i];
        sum+=board[i];
        remain[i]=board[i];
    }
    fin>>nrail;
    for(int i=0;i<nrail;i++)
        fin>>rail[i];
    fin.close();
 
    sort(board.begin(),board.begin()+nboard);
    sort(rail.begin(),rail.begin()+nrail);
 
    int temp=0;
    sumlen[0]=rail[0];
    while(temp<nrail && sumlen[temp]<=sum){
         ++temp;
         sumlen[temp]=sumlen[temp-1]+rail[temp];
    }
    nrail=temp;

    int i=nrail-1;
    for(;i>=0;--i){
        waste=0;
        maywaste=sum-sumlen[i];
        best=i;
        dfs(i,0);
    }
    if(i<0)fout<<0<<endl;
    return 0;
}