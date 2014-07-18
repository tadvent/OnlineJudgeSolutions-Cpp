/*
ID: wjl1241
PROG: kimbits
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;

//=========================================================================
// Too slow...

//int calcbits(unsigned long str){
//    str=(str&0x55555555)+((str>>1)&0x55555555);
//    str=(str&0x33333333)+((str>>2)&0x33333333);
//    str=(str&0x0F0F0F0F)+((str>>4)&0x0F0F0F0F);
//    str=(str&0x00FF00FF)+((str>>8)&0x00FF00FF);
//    return (str&0x0000FFFF)+((str>>16)&0x0000FFFF);
//}
//
//int main(){
//    ifstream fin("kimbits.in");
//    ofstream fout("kimbits.out");
//    int N,L,I;
//    unsigned long num=0;
//    fin>>N>>L>>I;
//
//    for(int cnt=0;cnt<I;++num){
//        //if(num>2100000000){fout<<"overflow!"<<endl;break;}
//        if(calcbits(num)<=L)++cnt;
//    }
//    --num;
//
//    for(int i=N-1;i>=0;--i){
//        fout<<((num>>i)&0x1);
//    }
//    fout<<endl;
//
//    return 0;
//}

//=======================================================================

class comb{
    static unsigned long matrix[32][32];
public:
    static void init(void){
        for(int i=0;i<32;++i){
            matrix[i][0]=1;
            matrix[i][1]=i;
            for(int j=2;j<32;++j)matrix[i][j]=0;
            matrix[i][i]=1;
        }
    }
    static unsigned long calc(int n, int r){
        //if(r>n)return 1;
        if(matrix[n][r])return matrix[n][r];
        matrix[n][r]=calc(n-1,r)+calc(n-1,r-1);
        return matrix[n][r];
    }
};

unsigned long comb::matrix[32][32];

unsigned long expen(int k, int l){
    unsigned long sum=0;
    int upper;
    if(0==k)return 1;
    upper=min(k,l);
    for(int i=0;i<upper;++i)sum+=comb::calc(k-1,i);
    return sum;
}

int main(){
    ifstream fin("kimbits.in");
    ofstream fout("kimbits.out");
    comb::init();
    int N,L;
    unsigned long I;
    fin>>N>>L>>I;

    unsigned long number=0;
    while(I>1){
        unsigned long sum=0,tmp;
        int k=0;
        while((tmp=sum+expen(k++,L))<I)sum=tmp;
        number=number|(0x1<<(k-2));
        I-=sum;
        --L;
    }

    for(int i=N-1;i>=0;--i){
        fout<<((number>>i)&0x1);
    }
    fout<<endl;

    return 0;
}