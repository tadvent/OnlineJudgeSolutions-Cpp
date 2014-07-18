#include<iostream>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
char A[6] = {0}, B[6] = {0};
int a, b, k;
int main(){
    while(cin>>A>>B>>k && (strcmp(A, "0") || strcmp(B, "0"))){
        char *pa = copy_backward(A, A+strlen(A), A+5);
        char *pb = copy_backward(B, B+strlen(B), B+5);
        fill(A, pa, '0');
        fill(B, pb, '0');
        if(k>5)k=5;
        if(equal(A+5-k, A+5, B+5-k))
            cout << "-1\n";
        else cout << atoi(pa) + atoi(pb) << '\n';
    }
}
