#include<cstdio>

int humble[5843] = {0, 1};

void init(){
    int idx2 = 1, idx3 = 1, idx5 = 1, idx7 = 1, idx = 2;
    while(idx < 5843){
        int n2 = 2*humble[idx2], n3 = 3*humble[idx3], n5 = 5*humble[idx5], n7 = 7*humble[idx7];
        int next = n2;
        if(next > n3)next = n3;
        if(next > n5)next = n5;
        if(next > n7)next = n7;
        if(next == n2)++idx2;
        if(next == n3)++idx3;
        if(next == n5)++idx5;
        if(next == n7)++idx7;
        humble[idx++] = next;
    }
}

int main(){
    int n;
    init();
    while(scanf("%d", &n) != EOF && n){
        int tail = n%10;
        printf("The %d", n);
        if(tail == 1 && n%100 != 11){
            fputs("st", stdout);
        } else if(tail == 2 && n%100 != 12){
            fputs("nd", stdout);
        } else if(tail == 3 && n%100 != 13){
            fputs("rd", stdout);
        } else {
            fputs("th", stdout);
        }
        printf(" humble number is %d.\n", humble[n]);
    }
}
