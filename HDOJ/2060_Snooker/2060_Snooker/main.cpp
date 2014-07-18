#include<iostream>
using namespace std;
int main(){
    int n, ball, psc, osc;
    cin>>n;
    while(n--){
        cin>>ball>>psc>>osc;
        if(ball > 0){
            switch(ball){
                case 6: psc += 2;
                case 5: psc += 3;
                case 4: psc += 4;
                case 3: psc += 5;
                case 2: psc += 6;
                case 1: psc += 7;
                    break;
                default:
                    psc += (ball-6) * 8 + 27;
            }
        }
        cout<< ((psc >= osc)? "Yes\n":"No\n");
    }
}
