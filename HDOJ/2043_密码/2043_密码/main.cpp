#include<iostream>
using namespace std;
bool checkwd(){
    int lower = 0, upper = 0, number = 0, symbol = 0, i;
    for(i=0; i<17; ++i){
        char c;
        if(!cin.get(c) || c=='\n')break;
        if(c >= 'a' && c <= 'z')lower = 1;
        else if(c >= 'A' && c <= 'Z')upper = 1;
        else if(c >= '0' && c <= '9')number = 1;
        else if(c == '~' || c == '!' || c == '@' || c == '#'
            || c == '$' || c == '%' || c == '^')symbol = 1;
    }
    if(i > 16)cin.ignore(INT_MAX, '\n');
    if(i < 8 || i > 16)return false;
    if(lower + upper + number + symbol >= 3)return true;
    else return false;
}
int main(){
    int n;
    cin>>n;
    cin.ignore(INT_MAX, '\n');
    while(n--){
        cout << (checkwd()? "YES\n":"NO\n");
    }
}