#include<cstdio>

bool job(){
    double sum = 0.0, mm;
    if(scanf("%lf", &mm) == EOF)return false;
    sum = mm;
    for(int i=1; i<12; ++i){
        scanf("%lf", &mm);
        sum += mm;
    }
    printf("$%.2f\n", sum/12);
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(job());
}
