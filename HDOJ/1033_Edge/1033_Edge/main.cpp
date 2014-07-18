#include<cstdio>

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int c;
    while((c=getchar()) != EOF){
        int dirx = 10, diry = 0, x = 310, y = 420, tmp;
        puts("300 420 moveto\n310 420 lineto");
        ungetc(c, stdin);

        while((c=getchar()) != EOF && c != '\n'){
            if(c == 'A'){
                tmp = -dirx;
                dirx = diry;
                diry = tmp;
            } else { // 'V'
                tmp = dirx;
                dirx = -diry;
                diry = tmp;
            }
            printf("%d %d lineto\n", x+=dirx, y+=diry);
        }
        puts("stroke\nshowpage");
    }
}
