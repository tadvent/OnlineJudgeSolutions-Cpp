#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

int str2longnum(string& numstr, vector<int>& longnum){
    string::size_type pos = numstr.find('.');
    int decpartlen = numstr.size() - pos - 1;
    numstr.erase(pos, 1);
    longnum.resize(1);
    istringstream is(numstr);
    is>>longnum.front();
    if(longnum.front() >= 10000){
        longnum.push_back(longnum.front() / 10000);
        longnum.front() %= 10000;
    }
    return decpartlen;
}
void calpow(vector<int>& longnum, int exp);

int main(){
    ifstream cin("i.txt");
    ofstream cout("o.txt");
    string numstr;
    int exponent, decpartlen;
    while(cin>>numstr>>exponent){
        vector<int> longnum;
        decpartlen = str2longnum(numstr, longnum);
        calpow(longnum, exponent);
        decpartlen *= exponent;
    }
}