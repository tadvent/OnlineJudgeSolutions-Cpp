/*
ID: wjl1241
PROG: fact4
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;

long fact5=0,fact2=0;
long calcfact(long num){
    while (num%10==0)num/=10;
    if((num&0x1)==0){ //can be devided by 2 but not 5
        do {
            num>>=1;
            ++fact2;
        }while((num&0x1)==0);
    }
    else {  //can be devided by 5 but not 2
        while(num%5==0){
            num/=5;
            ++fact5;
        }
    }

    return num%10;
}

int main(){
    ifstream fin("fact4.in");
    ofstream fout("fact4.out");
    long n,lastnum=1;
    fin>>n;

    for(long i=2;i<=n;++i){
        lastnum=(lastnum*calcfact(i))%10;
    }

    long tmp=min(fact2,fact5);
    fact2-=tmp;
    fact5-=tmp;
    if(fact2){
        for(long i=0;i<fact2;++i){
            lastnum=(lastnum<<1)%10;
        }
    }
    else {
        for(long i=0;i<fact5;++i){
            lastnum=(lastnum*5)%10;
        }
    }

    fout<<lastnum<<endl;
    return 0;
}