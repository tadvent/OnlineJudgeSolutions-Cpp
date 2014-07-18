#include<iostream>
#include<bitset>
using namespace std;
bitset<50> bits;
int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    int n, num;
    cin.tie(NULL);
    while(cin>>n && n>0){
        if(n <= 8){
            ++n;
            while(n--)
                cin.ignore(5000, '\n');
            cout << "No\n";
        }
        else {
            n *= 6;
            bits.set();
            bits.reset(0);
            while(n--){
                cin >> num;
                bits.reset(num);
            }
            if(bits.none())
                cout << "Yes\n";
            else
                cout << "No\n";
        }
    }
    cout.flush();
}
