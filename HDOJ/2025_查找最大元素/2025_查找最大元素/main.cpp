#include<iostream>
using namespace std;
char line[101];
int main(){
    char maxc;
    while(cin.getline(line,101)){
        maxc=0;
        char *p=line;
        while(*p){
            if(*p>maxc)maxc=*p;
            ++p;
        }
        p=line;
        while(*p){
            cout.put(*p);
            if(*p++==maxc)cout<<"(max)";
        }
        cout.put('\n');
    }
}