/*
ID: wjl1241
PROG: fence9
LANG: C++
*/

#include<fstream>
#include<limits>
using namespace std;

const float eps=10*numeric_limits<float>::epsilon();

ifstream fin("fence9.in");
ofstream fout("fence9.out");

int main(){
    int n,m,p,cnt=0;
    fin>>n>>m>>p;

    for(int y=1;y<m;++y){
        float x1,x2;
        x1=float(y)*n/m;
        x2=float(y)*(n-p)/m+p;
        cnt+=int(x2-eps)-int(x1+1)+1;
    }

    fout<<cnt<<endl;
}