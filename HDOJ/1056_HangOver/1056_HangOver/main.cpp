#include<cstdio>

int hangover(double len){
    int fenmu = 2;
    double sum = 0.0;
    while(sum < len - 1e-8){
        sum += 1.0/fenmu++;
    }
    return fenmu - 2;
}

int main(){
    double len;
    while(scanf("%lf", &len) != EOF && len > 1e-8)
        printf("%d card(s)\n", hangover(len));
}
