#include<fstream>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

struct decipher{
    void operator()(char &ch)const{
        if(ch >= 'A' && ch <= 'Z'){
            ch = (ch - 'A' + 21) % 26 + 'A';
        }
    }
};

int main(){
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    string cmd;

    while(cin>>cmd && cmd != "ENDOFINPUT"){
        string line;
        if(cmd == "START"){
            getline(cin, line);
            getline(cin, line);
            for_each(line.begin(), line.end(), decipher());
            cout<<line<<'\n';
        }
    }
}
