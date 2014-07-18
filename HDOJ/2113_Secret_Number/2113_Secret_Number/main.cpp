#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

class evensum{
    int sum;
public:
    evensum():sum(0){}
    void operator()(char ch){
        if((ch - '0') % 2 == 0){
            sum += ch - '0';
        }
    }
    operator int() const {
        return sum;
    }
};

int main(){
    bool first = true;
    string num;
    num.reserve(10);
    while(cin>>num){
        if(first)first = false;
        else cout.put('\n');
        cout << for_each(num.begin(), num.end(), evensum()) << '\n';
    }
}
