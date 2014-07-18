#include<cstdio>
#include<cctype>
#include<cstring>

int main(){
    int c, cnt[26]={0};
    while((c=getchar()) != EOF){
        if(c=='\n'){
            for(int i=0; i<26; ++i)
                printf("%c:%d\n", 'a'+i, cnt[i]);
            putchar('\n');
            memset(cnt, 0, sizeof(cnt));
        } else if(isalpha(c)){
            ++cnt[c-'a'];
        }
    }
}
