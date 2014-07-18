#include<cstdio>
#include<cmath>

int main(){
    int t, m, n;
    scanf("%d", &t);
    for(int i=1; i<=t; ++i){
        scanf("%d%d", &m, &n);
        if(!(m%2) || !(n%2)){
            printf("Scenario #%d:\n%.2f\n\n", i, (double)m*n);
        } else {
            printf("Scenario #%d:\n%.2f\n\n", i, (double)m*n -1.0 + sqrt(2.0));
        }
    }
}
