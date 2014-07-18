#include<fstream>
#include<iostream>
#include<string>
#include<list>
#include<deque>
using namespace std;

list<string> strlist;
typedef deque<list<string>::iterator> itrdeq;
itrdeq his;
itrdeq::iterator cur;

int main(){
    ifstream cin("in.txt");
    ofstream cout("out.txt");
    strlist.push_back("http://www.acm.org/");
    his.push_back(--strlist.end());
    cur = his.begin();

    string command;
    cin>>command;
    while(command != "QUIT"){
        if(command == "VISIT"){
            strlist.push_back(string());
            cin>>strlist.back();

            for(itrdeq::iterator i=cur+1; i!=his.end(); ++i)
                strlist.erase(*i);
            his.erase(++cur, his.end());
            his.push_back(--strlist.end());
            cur = --his.end();
            cout<<*(*cur)<<'\n';
        } else if(command == "BACK"){
            if(cur == his.begin()){
                cout<<"Ignored\n";
            } else {
                --cur;
                cout<<*(*cur)<<'\n';
            }
        } else if(command == "FORWARD"){
            if(cur+1 == his.end()){
                cout<<"Ignored\n";
            } else {
                ++cur;
                cout<<*(*cur)<<'\n';
            }
        }
        cin>>command;
    }
}