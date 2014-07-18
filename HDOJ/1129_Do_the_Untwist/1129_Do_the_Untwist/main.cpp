#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

class solver{
    int n, k;
    char text[80];
    struct ch2code{
        void operator()(char &c)const{
            if(c >= 'a' && c <= 'z'){
                c -= 'a' - 1;
            } else if(c == '_'){
                c = 0;
            } else if(c == '.'){
                c = 27;
            }
        }
    };
    struct code2ch{
        void operator()(char &c)const{
            if(c >= 1 && c <= 26){
                c += 'a' - 1;
            } else if(c == 0){
                c = '_';
            } else if(c == 27){
                c = '.';
            }
        }
    };
    void txt2code(){
        for_each(text, text+n, ch2code());
    }
    void code2txt(){
        for_each(text, text+n, code2ch());
    }
    void untwist(){
        char buf[80];
        for(int i=0; i<n; ++i){
            buf[k*i % n] = (text[i] + i) % 28;
        }
        memcpy(text, buf, n);
    }
public:
    bool read(){
        if(scanf("%d", &k) == EOF || !k)return false;
        scanf("%s", text);
        n = strlen(text);
        return true;
    }
    void solve(){
        txt2code();
        untwist();
        code2txt();
    }
    void write(){
        puts(text);
    }
};

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    solver sov;
    while(sov.read()){
        sov.solve();
        sov.write();
    }
}
