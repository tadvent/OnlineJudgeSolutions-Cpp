/*
ID: wjl1241
PROG: prefix
LANG: C++
*/

// DFS ... time limit exceeded , stack overflow...

//#include<fstream>
//#include<string>
//#include<stack>
//using namespace std;
//
//string instr;
//string primitive[2000];
//int longest;
//stack<int> tocheck;
//
//int hash(const string &str){    //return value: 0 - 1999
//    int rst=0;
//    for(int i=0;i<str.length();++i){
//        rst=(rst*31+str[i]-'A'+1)%2000;
//    }
//    return rst;
//}
//
//bool IsPrimitive(const string &str){
//    int h=hash(str);
//    while(!primitive[h].empty()){
//        if(str==primitive[h])return true;
//        h=(h+1)%2000;
//    }
//    return false;
//}
//
//void schprefix(void){
//    int idx=tocheck.top();
//    tocheck.pop();
//    for(int len=1;len<11 && idx+len<=instr.length();++len){  //check prefix of len
//        if(IsPrimitive(instr.substr(idx,len))){
//            if(idx+len>longest)longest=idx+len;
//            tocheck.push(idx+len);
//        }
//    }
//}
//
//int main(){
//    ifstream fin("prefix.in");
//    ofstream fout("prefix.out");
//
//    fin>>instr;
//    while(instr!="."){
//        int h=hash(instr);
//        while(!primitive[h].empty())h=(h+1)%2000;
//        primitive[h]=instr;
//        fin>>instr;
//    }
//    string tmp;
//    instr.clear();
//    while(fin>>tmp)instr+=tmp;  //the long string to search for prefix
//
//    longest=0;
//    tocheck.push(0);
//    while(!tocheck.empty())schprefix();
//
//    fout<<longest<<endl;
//}

// DFS end

//=========================================================================

// DP is demanded

#include<fstream>
#include<string>
#include<vector>
using namespace std;

string instr;
string primitive[2000];

int hash(const string &str, int first=0, int last=0){    //return value: 0 - 1999
    int rst=0;
    if (!last)last=str.length();
    for(int i=first;i<last;++i){
        rst=(rst*31+str[i]-'A'+1)%2000;
    }
    return rst;
}

bool IsPrimitive(const string &str, int first, int len){
    int last=first+len;
    int h=hash(str,first,last);
    while(!primitive[h].empty()){
        if(len == primitive[h].length()){
            int i=first,j=0;
            while(i!=last && str[i]==primitive[h][j++])++i;
            if(i==last)return true;
        }
        h=(h+1)%2000;
    }
    return false;
}

int main(){
    ifstream fin("prefix.in");
    ofstream fout("prefix.out");

    fin>>instr;
    while(instr!="."){
        int h=hash(instr);
        while(!primitive[h].empty())h=(h+1)%2000;
        primitive[h]=instr;
        fin>>instr;
    }
    string tmp;
    instr.clear();
    while(fin>>tmp)instr+=tmp;  //the long string to search for prefix

    vector<int> LongestPrefix;
    LongestPrefix.resize(instr.length()+1);
    LongestPrefix[instr.length()]=0;
    for(int idx=instr.length()-1;idx>=0;--idx){
        int longest=0;
        for(int len=1;len<11 && idx+len<=instr.length();++len){  //check prefix of len
            if(IsPrimitive(instr,idx,len)){
                if(len+LongestPrefix[idx+len]>longest)longest=len+LongestPrefix[idx+len];
            }
        }
        LongestPrefix[idx]=longest;
    }

    fout<<LongestPrefix[0]<<endl;
}