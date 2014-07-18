/*
ID: wjl1241
LANG: C++
TASK: bigbrn
*/

#include<cstdio>
#include<algorithm>
using namespace std;

const int maxsize = 1000;
int N;

int barn[maxsize+1][maxsize+1] = {0};

void input(){
    int t, row, col;
    FILE *fin = fopen("bigbrn.in", "r");
    fscanf(fin, "%d%d", &N, &t);
    while(t--){
        fscanf(fin, "%d%d", &row, &col);
        barn[row][col] = -1;
    }
    fclose(fin);
}

int maxsq(){
    int mxsq = 0;
    for(int i = 1; i <= N; ++i)
        for(int j = 1; j <= N; ++j){
            if(barn[i][j] == -1)barn[i][j] = 0;
            else if(barn[i-1][j] == 0 || barn[i][j-1] == 0)
                barn[i][j] = 1;
            else if(barn[i-1][j] == barn[i][j-1]){
                if(barn[i-barn[i-1][j]][j-barn[i-1][j]] == 0)
                    barn[i][j] = barn[i-1][j];
                else barn[i][j] = barn[i-1][j] + 1;
            } else {
                barn[i][j] = 1 + min(barn[i-1][j], barn[i][j-1]);
            }
            if(barn[i][j] > mxsq)mxsq = barn[i][j];
        }
    return mxsq;
}

void output(){
    FILE *fout = fopen("bigbrn.out", "w");
    fprintf(fout, "%d\n", maxsq());
    fclose(fout);
}

int main(){
    input();
    output();
}
