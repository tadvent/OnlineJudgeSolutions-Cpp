#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    int m, n, sqr, tri;
    while(cin>>m>>n){
        sqr=tri=0;
        if(m>n)swap(m,n);
        for(int i=m;i<=n;++i)
            if(i%2)
                tri+=i*i*i;
            else sqr+=i*i;
        cout<<sqr<<' '<<tri<<'\n';
    }
}