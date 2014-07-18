#include<iostream>
using namespace std;
int seq[3000];
bool flag[3000];
void fillflag(int n){
    for(int i=0;i<n;++i)flag[i]=false;
    for(int i=0;i<n;++i){
        flag[abs(seq[i]-seq[i+1])-1]=true;
    }
}
bool isJolly(int n){
    --n;
    fillflag(n);
    for(int i=0;i<n;++i){
        if(!flag[i])return false;
    }
    return true;
}
int main(){
    int n;
    while(cin>>n){
        for(int i=0;i<n;++i)cin>>seq[i];
        if(isJolly(n))cout<<"Jolly\n";
        else cout<<"Not jolly\n";
    }
    return 0;
}