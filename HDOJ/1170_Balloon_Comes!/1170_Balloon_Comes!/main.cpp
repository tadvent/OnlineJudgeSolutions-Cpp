#include<cstdio>

bool run(){
    char op;
    int l, r;
    if(scanf(" %c%d%d", &op, &l, &r) == EOF)return false;
    switch(op){
        case '+':
            printf("%d\n", l + r); break;
        case '-':
            printf("%d\n", l - r); break;
        case '*':
            printf("%d\n", l * r); break;
        case '/':
            if(l % r == 0){
                printf("%d\n", l/r);
            } else {
                printf("%.2f\n", double(l)/r);
            }
            break;
    }
    return true;
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--)if(!run())break;
}
