// 垃圾题目，叙述有问题
// Your program should be able to handle up to 100 cents. 
// 这句意思居然是最多只能用 100 个硬币！！
// 下面是错误解法

//#include<iostream>
//using namespace std;
//
//long long dp[6][251] = {0};
//int val[] = {0, 1, 5, 10, 25, 50};
//void init(){
//    dp[0][0] = 1;
//    for(int n = 0; n < 251; ++n)dp[1][n] = 1;
//    for(int m = 2; m <= 5; ++m){
//        for(int n = 0; n < 251; ++n){
//            long long sum = dp[m-1][n];
//            int idx = n - val[m];
//            while(idx >= 0){
//                sum += dp[m-1][idx];
//                idx -= val[m];
//            }
//            dp[m][n] = sum;
//        }
//    }
//}
//
//int main(){
//    int n;
//    init();
//    while(cin>>n && n>=0){
//        cout<<dp[5][n]<<'\n';
//    }
//}

//===========================================================
// 重新来过 暴力 - -
#include<iostream>
using namespace std;
int ans[251] = {0};
void init(){
    int s2, s3, s4, s5, c2, c3, c4, c5;
    for(int a=0; a<=100; ++a)
        for(int b=0; (s2=a+b)<=100 && (c2=a+b*5)<=250; ++b)
            for(int c=0; (s3=s2+c)<=100 && (c3=c2+c*10)<=250; ++c)
                for(int d=0; (s4=s3+d)<=100 && (c4=c3+d*25)<=250; ++d)
                    for(int e=0; (s5=s4+e)<=100 && (c5=c4+e*50)<=250; ++e)
                        ++ans[c5];
}
int main(){
    int n;
    init();
    while(cin>>n && n>=0)
        cout<<ans[n]<<'\n';
}
