//#include<fstream>
//#include<iostream>
//#include<iomanip>
//#include<algorithm>
//#include<numeric>
//#include<map>
//#include<string>
//using namespace std;
//
//inline int char2int(const char &ch){
//    static int charmap[] = {
//        2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9
//    };
//    return charmap[ch - 'A'];
//}
//struct charplus{
//    int operator()(int left, char right)const{
//        if(right >= 'A' && right <= 'Z'){
//            return left * 10 + char2int(right);
//        } else if(right >= '0' && right <= '9'){
//            return left * 10 + right - '0';
//        } else return left;
//    }
//};
//inline int str2int(const string& str){
//    return accumulate(str.begin(), str.end(), 0, charplus());
//}
//class numout{
//    ostream &o;
//    bool hasout;
//public:
//    numout(ostream &os):o(os), hasout(false){}
//    void operator()(const pair<int, int>& p){
//        if(p.second > 1){
//            hasout = true;
//            o<<setw(3)<<p.first/10000<<'-'<<setw(4)<<p.first%10000<<' '<<p.second<<'\n';
//        }
//    }
//    operator void*(){
//        return (void*)(hasout? 1:0);
//    }
//};
//
//int main(){
//    ifstream cin("in.txt");
//    ofstream cout("out.txt");
//
//    int n;
//    string line;
//    map<int, int> numcnt;
//
//    cin>>n;
//    getline(cin, line);
//    while(n--){
//        getline(cin, line);
//        ++numcnt[str2int(line)];
//    }
//
//    cout.fill('0');
//    if(!for_each(numcnt.begin(), numcnt.end(), numout(cout))){
//        cout<<"No duplicates."<<endl;
//    }
//}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// use sort instead of map

#include<fstream>
#include<iostream>
#include<algorithm>
#include<vector>
#include<iomanip>
#include<string>
#include<numeric>
#include<limits>
using namespace std;

vector<int> phonenums;

inline int char2int(const char &ch){
    static int charmap[] = {
        2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9
    };
    return charmap[ch - 'A'];
}
struct charplus{
    int operator()(int left, char right)const{
        if(right >= 'A' && right <= 'Z'){
            return left * 10 + char2int(right);
        } else if(right >= '0' && right <= '9'){
            return left * 10 + right - '0';
        } else return left;
    }
};
inline int str2int(const string& str){
    return accumulate(str.begin(), str.end(), 0, charplus());
}

int main(){
    ifstream cin("in.txt");
    ofstream cout("out.txt");
    int n;
    string line;

    cin>>n;
    cin.ignore(numeric_limits<int>::max(), '\n');
    phonenums.reserve(n);
    while(n--){
        getline(cin, line);
        phonenums.push_back(str2int(line));
    }
    sort(phonenums.begin(), phonenums.end());

    cout.fill('0');
    bool hasout = false;
    vector<int>::iterator first = phonenums.begin(), last;
    while(first != phonenums.end()){
        last = find_if(first + 1, phonenums.end(), bind2nd(not_equal_to<int>(), *first));
        if(last - first > 1){
            cout<<setw(3)<<(*first)/10000<<'-'<<setw(4)<<(*first)%10000<<' '
                << last - first <<'\n';
            hasout = true;
        }
        first = last;
    }
    if(!hasout)
        cout<<"No duplicates."<<endl;
}