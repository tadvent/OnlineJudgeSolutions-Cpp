#include<fstream>
#include<iostream>
using namespace std;
int main(){
    ifstream cin("i.txt");
    ofstream cout("o.txt");
    int p,e,i,d,n=0;
    while(cin>>p>>e>>i>>d){
        if(p==-1 && e==-1 && i==-1 && d==-1)break;
        int ret = (i-d)%33;
        if(ret<=0) ret += 33;
        ret += d;
        while((ret-p)%23 !=0 || (ret-e)%28 !=0) ret+=33;
        cout<<"Case "<<(++n)<<": the next triple peak occurs in "<<ret-d<<" days.\n";
    }
}