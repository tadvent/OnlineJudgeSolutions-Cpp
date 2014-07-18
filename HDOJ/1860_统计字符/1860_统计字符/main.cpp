#include<iostream>
#include<algorithm>
using namespace std;

int keyn, linen, cnt[6];
char keych[6], line[81];

void countch(char ch){
    for(int i=0; i< keyn; ++i){
        if(keych[i] == ch){
            ++cnt[i];
        }
    }
}

int main(){
    while(cin.getline(keych, 6) && keych[0] != '#'){
        keyn = cin.gcount() - 1;
        cin.getline(line, 81);
        linen = cin.gcount() - 1;
        memset(cnt, 0, sizeof(cnt));
        for_each(line, line + linen, countch);

        for(int i=0; i<keyn; ++i){
            cout << keych[i] << ' ' << cnt[i] << '\n';
        }
    }
}
