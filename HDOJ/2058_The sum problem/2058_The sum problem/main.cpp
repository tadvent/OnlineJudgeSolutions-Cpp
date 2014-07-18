// Slow...

//#include<iostream>
//using namespace std;
//int main(){
//    int m, n;
//    while(cin>>n>>m && (n || m)){
//        int sum = 1, a = 1, b = 1;
//        for(;;){
//            if(sum < m){
//                sum += ++b;
//                if(b>n)break;
//            } else if(sum > m){
//                sum -= a++;
//                if(a>b)break;
//            } else {
//                cout << '[' << a << ',' << b << ']' << '\n';
//                sum += ++b;
//                sum -= a++;
//                if(b>n)break;
//            }
//        }
//        cout << '\n';
//    }
//}

//////////////////////////////////////////////
#include<iostream>
#include<cmath>
using namespace std;
int main(){
    int m, n;
    while(cin>>n>>m && (n||m)){
        m *= 2;
        int p = (int)sqrt((double)m);
        while(p>0){
            if(m%p == 0){
                int q = m/p;
                if((p+q) % 2 == 1){
                    int a = (q-p+1)/2;
                    int b = (q+p-1)/2;
                    if(b<=n)cout<<'['<<a<<','<<b<<"]\n";
                    else break;
                }
            }
            --p;
        }
        cout.put('\n');
    }
}
