#include<iostream>
using namespace std;
int main(){
int s;
while(cin>>s){
if(s<0||s>100)cout<<"Score is error!\n";
else{s=9-s/10;if(s<0)s=0;if(s>4)s=4;cout<<char('A'+s)<<'\n';}
}
}
