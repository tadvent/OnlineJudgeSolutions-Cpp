#include<iostream>
using namespace std;
int main(){
    int n;
    char c;
    cin>>n;
    cin.ignore(INT_MAX,'\n');
    while(n--){
        bool valid=true, first=true;;
        while(cin.get(c) && c!='\n'){
            if(!valid)continue;
            if(c<'0'||c>'9'&&c<'A'||c>'Z'&&c<'a'&&c!='_'||c>'z'){
                valid=false;
                continue;
            }
            if(first&&c>='0'&&c<='9'){
                valid=false;
                continue;
            } else first=false;
        }
        if(valid)cout<<"yes\n";
        else cout<<"no\n";
    }
}