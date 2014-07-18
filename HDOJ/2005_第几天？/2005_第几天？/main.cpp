#include<iostream>
#include<numeric>
using namespace std;
int days[] = {31,28,31,30,31,30,31,31,30,31,30};
bool isleap(int year){
    return year%4==0&&((year%100!=0)||(year%400==0));
}
int main(){
    int y,m,d;
    char ch;
    partial_sum(days, days+sizeof(days)/sizeof(days[0]), days);
    while(cin>>y>>ch>>m>>ch>>d){
        if(m>1)d+=days[m-2];
        if(m>2&&isleap(y))++d;
        cout<<d<<'\n';
    }
}