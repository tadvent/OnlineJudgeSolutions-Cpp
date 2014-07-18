/*
ID: wjl1241
LANG: C++
TASK: theme
*/

#include<cstdio>
#include<numeric>
#include<algorithm>
using namespace std;
const int maxsize = 5001;

int longest(int vec[], int size){
    int maxlength = 0;
    int dist = size - 5;
    adjacent_difference(vec, vec + size, vec);
    while(dist >= maxlength && dist >= 5){
        int length = 1;
        for(int i = size - dist - 1; i > 0; --i){
            if(vec[i] == vec[i+dist]){
                length = (length == dist)? dist : length + 1;
            } else {
                if(length > maxlength)
                    maxlength = length;
                length = 1;
            }
        }
        if(length > maxlength)
            maxlength = length;
        --dist;
    }
    return maxlength < 5? 0:maxlength;
}

int main(){
    int N;
    int vec[maxsize];
    FILE *fp = fopen("theme.in", "r");
    fscanf(fp, "%d", &N);
    for(int i = 0; i < N; ++i)
        if(fscanf(fp, "%d", &vec[i]) == EOF)break;
    fclose(fp);
    fp = fopen("theme.out", "w");
    fprintf(fp, "%d\n", longest(vec, N));
    fclose(fp);
    return 0;
}
