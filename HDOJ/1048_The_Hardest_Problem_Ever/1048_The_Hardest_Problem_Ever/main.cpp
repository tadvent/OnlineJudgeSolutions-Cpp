#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

class decipher{
public:
    void operator()(char &ch)const{
        if(ch >= 'A' && ch <= 'Z'){
            if(ch >= 'F')ch -= 5;
            else ch += 21;
        }
    }
};

int main(){
    string line;
    while(getline(cin, line) && line != "ENDOFINPUT"){
        if(line == "START" || line == "END")continue;
        for_each(line.begin(), line.end(), decipher());
        cout<< line << '\n';
    }
}
