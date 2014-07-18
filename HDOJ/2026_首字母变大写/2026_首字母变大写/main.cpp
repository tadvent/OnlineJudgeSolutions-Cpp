#include<iostream>
using namespace std;
int main(){
    char c;
    bool space=true;
    while(cin.get(c)){
        if(space){
            if(c>='a'&&c<='z'){
                c-='a'-'A';
                space=false;
            }else if(c>='A'&&c<='Z')space=false;
        }else if(c<'A'||c>'Z'&&c<'a'||c>'z')space=true;
        cout.put(c);
    }
}