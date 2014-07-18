#include<cstdio>
#include<cstring>

unsigned strhash(char *s){
    unsigned h = 0;
    while(*s){
        h = h*131 + *s++;
    }
    return h;
}
int hashtab[23];
void init(){
    char* strs[] = {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };
    for(int i=0; i<23; ++i)hashtab[i] = -1;
    for(int i=0; i<10; ++i)hashtab[strhash(strs[i])%23] = i;
}
int indigit(){ // return -1 if finished
    char str[10];
    if(scanf("%s", str) == EOF)return -1;
    if(*str < 'a' || *str > 'z')return -1;
    return hashtab[strhash(str)%23];
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    init();
    int a,b,d;
    while((d = indigit()) != -1){
        a = d;
        while((d = indigit()) != -1)a = a*10 + d;
        b = 0;
        while((d = indigit()) != -1)b = b*10 + d;
        if(a == 0 && b == 0)break;
        printf("%d\n", a+b);
    }
}
