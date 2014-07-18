#include<cstdio>

//int lowest(int num){
//    int rst = 1;
//    while((num & 1) == 0){
//        num >>= 1;
//        rst <<= 1;
//    }
//    return rst;
//}

inline int lowest2(int num){
    return num & (num ^ (num-1));
}

int main(){
    int num;
    while(scanf("%d", &num) != EOF && num != 0)
        printf("%d\n", lowest2(num));
}
