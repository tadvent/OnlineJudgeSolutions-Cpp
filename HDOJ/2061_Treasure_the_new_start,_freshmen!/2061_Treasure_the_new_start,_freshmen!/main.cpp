#include<iostream>
using namespace std;

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int N, K;
    char cname[31];
    bool first = true, invalid;
    double c, s, sumc, sums;
    cout.setf(ios::fixed);
    cout.precision(2);

    cin>>N;
    while(N--){
        if(first)first = false;
        else cout.put('\n');
        sumc = 0.0;
        sums = 0.0;
        invalid = false;

        cin>>K;
        while(K--){
            cin>>cname>>c>>s;
            if(invalid)continue;
            if(s < 60.0){
                invalid = true;
                continue;
            }
            sumc += c;
            sums += c * s;
        }
        if(invalid)
            cout << "Sorry!\n";
        else cout << sums/sumc << '\n';
    }
}
