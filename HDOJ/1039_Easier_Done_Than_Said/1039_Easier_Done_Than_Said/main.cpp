#include<cstdio>
#include<cstring>

bool canAC(const char *line){
    const static bool isVowel[] = {
        1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0
    };
    int lastch = 0; // 1: vowel; 2: consonant
    int lastcnt = 0, vowcnt = 0;
    for(; *line; ++line){
        if(*line == *(line-1) && *line != 'e' && *line != 'o')return false;
        if(isVowel[*line - 'a']){  // vowel
            ++vowcnt;
            if(lastch == 1){
                if(++lastcnt >= 3)return false;
            } else {
                lastcnt = 1;
                lastch = 1;
            }
        } else {  // consonant
            if(lastch == 2){
                if(++lastcnt >= 3)return false;
            } else {
                lastcnt = 1;
                lastch = 2;
            }
        }
    }
    if(!vowcnt)return false;  // no vowel
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    char line[25] = {0};
    while(gets(line+1) && strcmp(line+1, "end")){
        if(canAC(line+1)){
            printf("<%s> is acceptable.\n", line+1);
        } else {
            printf("<%s> is not acceptable.\n", line+1);
        }
    }
}
