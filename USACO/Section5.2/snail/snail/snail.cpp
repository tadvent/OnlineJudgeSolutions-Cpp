/*
ID: wjl1241
LANG: C++
TASK: snail
*/

#include<cstdio>
using namespace std;
char map[125][125] = {0};

int walk(int x, int y, int dir){
    // start at (x,y), along the dir direction
    // return the max steps can walk (including the initial square)
    // dir : right 1, down 2, left 3, up 4
    int steps = 1, len1 = 0, len2 = 0;
    map[x][y] = 1;
    int i = x, j = y;
    switch(dir){
        case 1: // right
            while(map[i][j+1] == 0){
                map[i][++j] = 1;
                ++steps;
            }
            if(map[i][j+1] == -1){ // barrier
                if(map[i-1][j] == 0)
                    len1 = walk(i-1, j, 4);
                if(map[i+1][j] == 0)
                    len2 = walk(i+1, j, 2);
                steps += len1>len2? len1:len2;
            } 
            for(int k = y; k <= j; ++k)
                map[x][k] = 0;
            break;
        case 2: // down
            while(map[i+1][j] == 0){
                map[++i][j] = 1;
                ++steps;
            }
            if(map[i+1][j] == -1){ // barrier
                if(map[i][j-1] == 0)
                    len1 = walk(i, j-1, 3);
                if(map[i][j+1] == 0)
                    len2 = walk(i, j+1, 1);
                steps += len1>len2? len1:len2;
            } 
            for(int k = x; k <= i; ++k)
                map[k][y] = 0;
            break;
        case 3: // left
            while(map[i][j-1] == 0){
                map[i][--j] = 1;
                ++steps;
            }
            if(map[i][j-1] == -1){ // barrier
                if(map[i-1][j] == 0)
                    len1 = walk(i-1, j, 4);
                if(map[i+1][j] == 0)
                    len2 = walk(i+1, j, 2);
                steps += len1>len2? len1:len2;
            } 
            for(int k = y; k >= j; --k)
                map[x][k] = 0;
            break;
        case 4: // up
            while(map[i-1][j] == 0){
                map[--i][j] = 1;
                ++steps;
            }
            if(map[i-1][j] == -1){ // barrier
                if(map[i][j-1] == 0)
                    len1 = walk(i, j-1, 3);
                if(map[i][j+1] == 0)
                    len2 = walk(i, j+1, 1);
                steps += len1>len2? len1:len2;
            } 
            for(int k = x; k >= i; --k)
                map[k][y] = 0;
            break;
        default:
            ;
    }
    return steps;
}

int main(){
    int n, m;
    FILE *fp = fopen("snail.in", "r");
    fscanf(fp, "%d%d", &n, &m);
    fgetc(fp);
    while(m--){
        char ch;
        int idx;
        fscanf(fp, "%c%d", &ch, &idx);
        map[idx][ch - 'A' + 1] = -1;
        fgetc(fp);
    }
    fclose(fp);

    for(int i = 0; i <= n+1; ++i)
        map[0][i] = map[n+1][i] = map[i][0] = map[i][n+1] = -1;
    int len1 = 0, len2 = 0;
    if(map[1][2] == 0)
        len1 = walk(1, 1, 1);
    if(map[2][1] == 0)
        len2 = walk(1, 1, 2);

    fp = fopen("snail.out", "w");
    fprintf(fp, "%d\n", len1 > len2? len1:len2);
    fclose(fp);
    return 0;
}
