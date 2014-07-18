/*
ID: wjl1241
PROG: sort3
LANG: C++
*/

#include<fstream>
using namespace std;

int n;
int num[1000];

int main(){
    ifstream fin("sort3.in");
    ofstream fout("sort3.out");

    int swapcnt=0,f1t2=0,f1t3=0,f2t1=0,f2t3=0,f3t1=0,f3t2=0;
    int cnt[3]={0,0,0};

    fin>>n;
    for(int i=0;i<n;++i){
        fin>>num[i];
        ++cnt[num[i]-1];
    }

    for(int i=0;i<cnt[0];++i){
        switch(num[i]){
            case 2:
                ++f1t2;
                break;
            case 3:
                ++f1t3;
                break;
        }
    }
    for(int i=cnt[0];i<cnt[0]+cnt[1];++i){
        switch(num[i]){
            case 1:
                ++f2t1;
                break;
            case 3:
                ++f2t3;
                break;
        }
    }
    for(int i=cnt[0]+cnt[1];i<n;++i){
        switch(num[i]){
            case 1:
                ++f3t1;
                break;
            case 2:
                ++f3t2;
                break;
        }
    }

    int tmp=min(f1t3,f3t1);
    swapcnt+=tmp;
    f1t3-=tmp;
    f3t1-=tmp;
    tmp=min(f1t2,f2t1);
    swapcnt+=tmp;
    f1t2-=tmp;
    f2t1-=tmp;
    tmp=min(f2t3,f3t2);
    swapcnt+=tmp;
    f2t3-=tmp;
    f3t2-=tmp;

    tmp=max(f1t2,f1t3);
    swapcnt+=tmp*2;

    fout<<swapcnt<<endl;
    return 0;
}