#include<cstdio>
#include<deque>
using namespace std;

struct mat{
    int x, y;
};

inline int mult(mat &l, const mat &r){
    if(l.y != r.x)return -1;
    l.y = r.y;
    return l.x * r.x * r.y;
}

deque<mat> st;
mat mats[26];
int n;

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    char c;
    scanf("%d", &n);
    while(n--){
        scanf(" %c", &c);
        scanf("%d%d ", &mats[c - 'A'].x, &mats[c - 'A'].y);
    }
    int rst, tmp;
    while((c = getchar()) != EOF){
        ungetc(c, stdin);
        rst = 0;
        bool err = false;
        while((c = getchar()) != '\n'){
            if(err)continue;
            if(c == ')'){
                if((tmp = mult(st[st.size()-2], st.back())) < 0){
                    err = true;
                } else {
                    rst += tmp;
                    st.pop_back();
                }
            } else if(c >= 'A' && c <= 'Z'){
                st.push_back(mats[c-'A']);
            }
        }
        if(err){
            puts("error");
        } else {
            printf("%d\n", rst);
        }
    }
}
