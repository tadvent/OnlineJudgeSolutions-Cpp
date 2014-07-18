#include<iostream>
#include<cstdlib>
using namespace std;
inline long long lllabs(long long a){
    return (a<0)?-a:a;
}
int main(){
    int m,n;
    while(cin>>m>>n){
        long long score, maxscore = 0;
        int num=m*n, idx, maxidx = 0;
        for(idx=0;idx<num;++idx){
            cin>>score;
            if(lllabs(score)>lllabs(maxscore)){
                maxscore=score;
                maxidx=idx;
            }
        }
        div_t d=div(maxidx, n);
        cout<<d.quot+1<<' '<<d.rem+1<<' '<<maxscore<<'\n';
    }
}
