#include<iostream>
#include<string>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
set<string> dic;
string argstr;
int num;

void arrange(const string &str, vector<bool> &chstate, size_t remain){
    if(remain==0){
        if(dic.find(argstr)!=dic.end()){
            cout<<argstr<<'\n';
            ++num;
        }
        return;
    }
    unsigned int idx=0;
    while(chstate[idx])++idx;
    char last=str[idx]-1;
    for(;idx<chstate.size();++idx){
        if(chstate[idx]||str[idx]<=last)continue;
        last=str[idx];
        argstr+=str[idx];
        chstate[idx]=true;
        arrange(str,chstate,remain-1);
        chstate[idx]=false;
        argstr.resize(argstr.length()-1);
    }
}

void lookup(string &instr){
    sort(instr.begin(),instr.end());
    vector<bool>chstate;
    chstate.reserve(6);
    for(unsigned int i=0;i<instr.length();++i)chstate.push_back(false);
    num=0;
    argstr.clear();
    arrange(instr,chstate,instr.length());
}

int main(){
    string idivider("XXXXXX");
    string odivider("******");
    string temp;
    cin>>temp;
    while(temp!=idivider){
        dic.insert(temp);
        cin>>temp;
    }
    cin>>temp;
    while(temp!=idivider){
        lookup(temp);
        if(num==0)cout<<"NOT A VALID WORD\n";
        cout<<odivider<<'\n';
        cin>>temp;
    }
}
