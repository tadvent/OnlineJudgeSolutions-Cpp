// Big Num ...

#include<cstdio>
#include<vector>
using namespace std;

class BigInt{
    vector<int> digits;
public:
    BigInt(const BigInt &r):digits(r.digits){}
    BigInt(int n = 0){
        do{
            digits.push_back(n%10000);
            n /= 10000;
        }while(n);
    }
    BigInt& operator=(const BigInt &r){
        digits = r.digits;
        return *this;
    }
    BigInt& operator+=(const BigInt &r){
        int i, c = 0;
        digits.resize(max(digits.size(), r.digits.size())+1);
        for(i=0; i<(int)r.digits.size(); ++i){
            digits[i] += r.digits[i] + c;
            c = digits[i]/10000;
            digits[i] %= 10000;
        }
        while(c){
            digits[i] += c;
            c = digits[i]/10000;
            digits[i] %= 10000;
            ++i;
        }
        if(digits.back() == 0)digits.pop_back();
        return *this;
    }
    BigInt& multi2(){
        digits.push_back(0);
        for(int i=0, c=0; i<(int)digits.size(); ++i){
            digits[i] += digits[i]+c;
            c = digits[i]/10000;
            digits[i] %= 10000;
        }
        if(digits.back() == 0)digits.pop_back();
        return *this;
    }
    void output(FILE *fp)const{
        vector<int>::const_reverse_iterator it = digits.rbegin();
        fprintf(fp, "%d", *it++);
        while(it != digits.rend()){
            fprintf(fp, "%04d", *it++);
        }
    }
};

BigInt num00[1001] = {0,0,1};
void init(){
    BigInt num1(1);
    for(int t=3; t<=1000; ++t){
        num00[t] = num00[t-2];
        num00[t] += num1;
        num1.multi2();
    }
}

int main(){
    init();
    int n;
    while(scanf("%d", &n) != EOF){
        num00[n].output(stdout);
        putchar('\n');
    }
}
