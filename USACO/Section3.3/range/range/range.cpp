/*
ID: wjl1241
PROG: range
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;

vector< vector<int> > vvMatrix;

int main(){
    ifstream fin("range.in");
    ofstream fout("range.out");
    int N;
    fin>>N;
    ++N;
    vvMatrix.resize(N);
    vvMatrix[0].resize(N,0);
    for(int i=1;i<N;++i){
        char inch;
        vvMatrix[i].resize(N);
        vvMatrix[i][0]=0;
        for(int j=1;j<N;++j){
            fin>>inch;
            switch(inch){
                case '0':
                    vvMatrix[i][j]=0;
                    break;
                case '1':
                    vvMatrix[i][j]=min(vvMatrix[i-1][j-1],min(vvMatrix[i-1][j],vvMatrix[i][j-1]))+1;
                    break;
            }
        }
    }

    vector<int> vSum(N,0);
    for(int i=1;i<N;++i)for(int j=1;j<N;++j){
        ++vSum[vvMatrix[i][j]];
    }
    for(int i=N-2;i>1;--i)vSum[i]+=vSum[i+1];
    for(int i=2;i<N;++i){
        if(vSum[i]){
            fout<<i<<' '<<vSum[i]<<'\n';
        }
        else break;
    }
}