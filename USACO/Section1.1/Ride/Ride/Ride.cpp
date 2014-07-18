/*
ID: wjl1241
PROG: ride
LANG: C++
*/

#include<fstream>
#include<string>
using namespace std;

int calnum(const string &str){
    int num=1;
    for(int i=0;i<(int)str.length();i++)num*=int(str[i])-64;
    return num%47;
}

int main(){
    ofstream fout("ride.out");
    ifstream fin("ride.in");
    string comet,group;

    fin>>comet>>group;
    if(calnum(comet)==calnum(group))
        fout<<"GO"<<endl;
    else fout<<"STAY"<<endl;
    return 0;
}