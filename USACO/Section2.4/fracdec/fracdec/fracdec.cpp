/*
ID: wjl1241
PROG: fracdec
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;

struct eachbit{
    eachbit(int rst, int rmn):result(rst),remain(rmn){}
    int result;
    int remain;
};

int main(){
    ifstream fin("fracdec.in");
    ofstream fout("fracdec.out");
    int n,d,tmp,fracpart,printnum=0;
    vector<eachbit> calc;
    fin>>n>>d;
    if(0==d)return -1;
    calc.resize(d,eachbit(0,0));
    if(n>=d){
        tmp=n/d;
        fout<<tmp;
        while(tmp){
            ++printnum;
            tmp/=10;
        }
    }
    else {
        fout<<0;
        ++printnum;
    }
    fout<<'.';
    ++printnum;
    n%=d;
    fracpart=n;

    if(0==fracpart){
        fout<<0<<endl;
        return 0;
    }

    int cycbegin=0;
    while(n){
        if(calc[n].remain){
            cycbegin=n;
            break;
        }
        tmp=n*10;
        calc[n].result=tmp/d;
        calc[n].remain=tmp%d;
        n=tmp%d;
    }
    if(0==n){
        n=fracpart;
        while(n){
            fout<<calc[n].result;
            if(0==++printnum%76)fout<<'\n';
            n=calc[n].remain;
        }
        if(0!=printnum%76)fout<<endl;
    }
    else {
        n=fracpart;
        while(n!=cycbegin){
            fout<<calc[n].result;
            if(0==++printnum%76)fout<<'\n';
            n=calc[n].remain;
        }
        fout<<'(';
        ++printnum;
        do{
            fout<<calc[n].result;
            if(0==++printnum%76)fout<<'\n';
            n=calc[n].remain;
        }while(n!=cycbegin);
        fout<<')'<<endl;
    }

    return 0;
}