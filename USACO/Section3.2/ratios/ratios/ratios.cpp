/*
ID: wjl1241
PROG: ratios
LANG: C++
*/

#include<fstream>
#include<valarray>
using namespace std;

typedef valarray<int> Ratio;
Ratio mixture[3];
Ratio goal;

inline int calc(const Ratio &r1, const Ratio &r2, const Ratio &r3){
    return r1[0]*(r2[1]*r3[2]-r2[2]*r3[1])-r2[0]*(r1[1]*r3[2]-r1[2]*r3[1])+r3[0]*(r1[1]*r2[2]-r1[2]*r2[1]);
}

int gcd(int a, int b){
    if(a<b)swap(a,b);
    if(0==b)return a;
    int c=a%b;
    while(c){
        a=b;
        b=c;
        c=a%b;
    }
    return b;
}

int main(){
    ifstream fin("ratios.in");
    ofstream fout("ratios.out");
    goal.resize(3,0);
    for(int i=0;i<3;++i)fin>>goal[i];
    for(int i=0;i<3;++i){
        mixture[i].resize(3,0);
        for(int j=0;j<3;++j)fin>>mixture[i][j];
    }
    int n=calc(mixture[0],mixture[1],mixture[2]);
    int x1=calc(goal,mixture[1],mixture[2]);
    int x2=calc(mixture[0],goal,mixture[2]);
    int x3=calc(mixture[0],mixture[1],goal);
    if(n<0){x1=-x1;x2=-x2;x3=-x3;n=-n;}

    if(x1<0 || x2<0 || x3<0)fout<<"NONE"<<endl;
    else {
        int g=gcd(x1,x2);
        g=gcd(g,x3);
        g=gcd(g,n);
        fout<<x1/g<<' '<<x2/g<<' '<<x3/g<<' '<<n/g<<endl;
    }

    return 0;
}