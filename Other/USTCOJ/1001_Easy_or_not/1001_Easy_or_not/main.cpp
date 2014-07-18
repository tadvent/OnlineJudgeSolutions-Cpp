//#include<cstdio>
//int main(){
//    int c;
//    while((c=getchar()) != EOF)putchar(c);
//}

#include<cstdio>
#define bufsize (32*1024)
int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    char buf[bufsize];
    int readcnt;
    while((readcnt = fread(buf, 1, bufsize, stdin)) == bufsize)
        fwrite(buf, 1, bufsize, stdout);
    fwrite(buf, 1, readcnt, stdout);
}
