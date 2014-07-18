/*
ID: wjl1241
PROG: namenum
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<utility>
using namespace std;

string calnumstr(const string& instr){
    string outstr;
    for(int i=0;i<instr.length();i++){
        char num;
        if(instr[i]<='Q'){
            num=static_cast<char>((static_cast<int>(instr[i])-65)/3+50);
        }
        else {
            num=static_cast<char>((static_cast<int>(instr[i])-66)/3+50);
        }
        outstr+=num;
    }
    return outstr;
};

int main(){
    ifstream fdic("dict.txt");
    ifstream fin("namenum.in");
    ofstream fout("namenum.out");

    vector<pair<string,string> > dicstr;
    dicstr.reserve(5000);
    string readinstr;
    while(fdic>>readinstr){
        dicstr.push_back(pair<string,string>(readinstr,calnumstr(readinstr)));
    }
    fdic.close();

    fin>>readinstr;
    bool invalidname=true;
    for(int i=0;i<dicstr.size();i++){
        if(readinstr==dicstr[i].second){
            if(invalidname)invalidname=false;
            fout<<dicstr[i].first<<endl;
        }
    }
    if(invalidname)fout<<"NONE"<<endl;

    return 0;
}