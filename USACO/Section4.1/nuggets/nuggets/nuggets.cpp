/*
ID: wjl1241
PROG: nuggets
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;

int gcd(int a, int b){
    if(a<b)swap(a,b);
    int c=a%b;
    while(c){
        a=b;
        b=c;
        c=a%b;
    }
    return b;
}

bool makeup[257]={0};
vector<int> base;

int main(){
    ifstream fin("nuggets.in");
    ofstream fout("nuggets.out");
    int nBase;
    fin>>nBase;
    base.resize(nBase,0);
    for(int i=0;i<nBase;++i)fin>>base[i];

    int g=base[0];
    for(int i=1;i<nBase;++i)g=gcd(base[i],g);
    if(g>1){
        fout<<0<<endl;
        return 0;
    }

    for(int i=0;i<nBase;++i)makeup[base[i]]=true;
    int pos=1,last=0;
    while(pos-last<=257){
        if(makeup[pos%257]){
            for(int i=0;i<nBase;++i)makeup[(pos+base[i])%257]=true;
        }
        else {
            last=pos;
        }
        makeup[pos%257]=false;
        ++pos;
    }
    fout<<last<<endl;
    return 0;
}