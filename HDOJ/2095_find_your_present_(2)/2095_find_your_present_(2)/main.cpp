//#include<cstdio>
//int main(){
//    int n, num, cur;
//    while((scanf("%d", &n) != EOF) && n){
//        num = 0;
//        while(n--){
//            scanf("%d", &cur);
//            num ^= cur;
//        }
//        printf("%d\n", num);
//    }
//}

// try to use stream
#include<iostream>
#include<locale>
using namespace std;
int main(){
    long n, num, cur;
    ios::iostate st;
    while(cin>>n && n){
        num = 0;
        while(n--){
            cin.rdbuf()->sbumpc();
            use_facet<num_get<char> >(locale::classic()).get(
                istreambuf_iterator<char>(cin), istreambuf_iterator<char>(), cin, st, cur);
            num ^= cur;
        }
        cout << num << '\n';
    }
}
