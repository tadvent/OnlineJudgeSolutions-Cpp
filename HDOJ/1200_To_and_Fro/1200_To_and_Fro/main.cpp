#include<cstdio>

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    char mat[100][20];
    int w;

    while(scanf("%d", &w) != EOF && w){
        while(getchar() != '\n');
        int line=0, pos=0, dir=1, c;
        while((c=getchar()) != '\n'){
            mat[line][pos] = c;
            pos += dir;
            if(pos < 0){
                ++line;
                pos = 0;
                dir = 1;
            } else if(pos >= w){
                ++line;
                pos = w-1;
                dir = -1;
            }
        }
        for(int j=0; j<w; ++j)for(int i=0; i<line; ++i)
            putchar(mat[i][j]);
        putchar('\n');
    }
}
