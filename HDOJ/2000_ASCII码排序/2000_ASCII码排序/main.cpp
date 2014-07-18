#include<iostream>
#include<algorithm>
using namespace std;
char str[5];
int main(){
    while(cin.getline(str, 5)){
        sort(str, str+3);
        cout<<str[0]<<' '<<str[1]<<' '<<str[2]<<'\n';
    }
}