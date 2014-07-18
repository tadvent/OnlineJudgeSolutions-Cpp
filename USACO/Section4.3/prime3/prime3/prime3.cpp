/*
ID: wjl1241
PROG: prime3
LANG: C++
*/

#include<fstream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

//bool none = true;
//
class PrimeChecker{
    static bool checkcur(unsigned current, unsigned base){
        unsigned divider = (primes[base] == 1)? primes[base-1]:primes[base];
        while(divider > 2){
            if(current % divider == 0)return false;
            divider = primes[divider-1];
        }
        return true;
    }
protected:
    static vector<unsigned> primes;
public:
    PrimeChecker(){}
    PrimeChecker(unsigned MaxInt){
        Init(MaxInt);
    }
    static void Init(unsigned MaxInt){
        if(MaxInt < 5)MaxInt = 5;
        if(MaxInt < primes.size())return;
        unsigned current = max(0, int(primes.size()) - 1), lastprime;
        primes.resize(MaxInt + 2);  // last num to avoid index outrange
        if(current < 5){
            primes[0] = primes[1] = 0;
            primes[2] = primes[3] = 1;
            primes[4] = 3;
            current = 5;
        }
        lastprime = (primes[current-1] == 1)?primes[current-2]:primes[current-1];

        unsigned maxbase = static_cast<unsigned>(sqrt(double(MaxInt)));
        unsigned base    = static_cast<unsigned>(sqrt(double(current))) + 1;//...
        if(current % 2 == 0)primes[current++] = lastprime;  // adjust current to odd
        for(; base <= maxbase; ++base){
            unsigned curmax = base * base;
            while(current < curmax){
                if(checkcur(current, base)){
                    lastprime = current;
                    primes[current++] = 1;
                } else
                    primes[current++] = lastprime;
                primes[current++] = lastprime;
            }
        }
        while(current <= MaxInt){
            if(checkcur(current, maxbase+1)){
                lastprime = current;
                primes[current++] = 1;
            } else
                primes[current++] = lastprime;
            primes[current++] = lastprime;
        }
    }
    static bool IsPrime(unsigned Num){
        return primes[Num] == 1;
    }
};
vector<unsigned> PrimeChecker::primes;

class ValidChecker : protected PrimeChecker {
    bool checksum(unsigned num) const {
        unsigned sum = 0;
        while(num != 0){
            sum += num%10;
            num /= 10;
        }
        return sum == Sum;
    }
protected:
    unsigned Sum;
    vector<unsigned> nums;
public:
    ValidChecker(){}
    ValidChecker(unsigned sum){
        Reset(sum);
    }
    void Reset(unsigned sum){
        Sum = sum;
        PrimeChecker::Init(100000);
        nums = PrimeChecker::primes;
        int lastvalid = 100000;
        nums[100000] = 100000;
        for(int current = 99999; current > 10000;){
            if(nums[current] == 1 && checksum(current))
                lastvalid = current--;
            else nums[current--] = lastvalid;
            nums[current--] = lastvalid;
        }
    }
    bool IsValid(unsigned Num) const {
        return nums[Num] == 1;
    }
    unsigned NextValid(unsigned Cur) const {
        return (nums[Cur] == 1)?nums[Cur+1]:nums[Cur];
    }
};

ValidChecker vc;
int numdigits[5][5];
int Prefix;

void numtodigits(unsigned num, int digits[5]){
    int i = 5;
    while(--i >= 0){
        digits[i] = num % 10;
        num /= 10;
    }
}
unsigned digitstonum(int digits[5]){
    unsigned num = 0;
    for(int i=0;i<5;++i)
        num = num*10+digits[i];
    return num;
}

class LESS{
public:
    bool operator()(const vector<int> *p1, const vector<int> *p2) const {
        for(int i=0; i<25; ++i){
            if((*p1)[i] < (*p2)[i])return true;
            if((*p1)[i] > (*p2)[i])return false;
        }
        return false;
    }
};
class Result{
    vector< vector<int>* > vnums;
    void printable(vector<int>* p, ostream &o){
        for(int i=0; i<25; ++i){
            o<<(*p)[i];
            if((i+1) % 5 == 0)o<<'\n';
        }
    }
public:
    friend class LESS;
    void add(){
        vnums.push_back(new vector<int>(&numdigits[0][0],&numdigits[5][0]));
    }
    void sort(){
        std::sort(vnums.begin(),vnums.end(),LESS());
    }
    void print(ostream &o){
        if(vnums.empty()){
            o<<"NONE"<<endl;
            return;
        }
        printable(*vnums.begin(),o);
        for(int i=1; i<int(vnums.size()); ++i){
            o<<'\n';
            printable(vnums[i],o);
        }
    }
    ~Result(){
        for(vector<vector<int>*>::iterator itr=vnums.begin(); itr!=vnums.end(); ++itr)
            delete *itr;
    }
}result;

inline bool nozero(int digits[5]){
    return (digits[0]!=0 && digits[1]!=0 && digits[2]!=0 && digits[3]!=0 && digits[4]!=0);
}

struct X____{   // pattern X____ and all digits are non-zero
    int digits[4];
    void set(int Digits[5]){
        digits[0] = Digits[1];
        digits[1] = Digits[2];
        digits[2] = Digits[3];
        digits[3] = Digits[4];
    }
};
struct X___X{   // pattern X___X
    int digits[3];
    void set(int Digits[5]){
        digits[0] = Digits[1];
        digits[1] = Digits[2];
        digits[2] = Digits[3];
    }
};
struct X_X__{   // pattern X_X__
    int digits[3];
    void set(int Digits[5]){
        digits[0] = Digits[1];
        digits[1] = Digits[3];
        digits[2] = Digits[4];
    }
};
struct XX_X_{   // pattern XX_X_
    int digits[2];
    void set(int Digits[5]){
        digits[0] = Digits[2];
        digits[1] = Digits[4];
    }
};
struct XXXX_{   // pattern XXXX_
    int digit;
    void set(int Digits[5]){
        digit = Digits[4];
    }
};

vector<X____> pat1[10];
vector<X___X> pat2[10][10];
vector<X_X__> pat3[10][10];
vector<XX_X_> pat4[10][10][10];
vector<XXXX_> pat5[10][10][10][10];

void initpats(void){
    X____ p1;
    X___X p2;
    X_X__ p3;
    XX_X_ p4;
    XXXX_ p5;
    int digits[5];

    for(int num = vc.NextValid(10000); num < 100000;){
        numtodigits(num, digits);
        if(nozero(digits)){
            p1.set(digits);
            pat1[digits[0]].push_back(p1);
        }
        p2.set(digits);
        pat2[digits[0]][digits[4]].push_back(p2);
        p3.set(digits);
        pat3[digits[0]][digits[2]].push_back(p3);
        p4.set(digits);
        pat4[digits[0]][digits[1]][digits[3]].push_back(p4);
        p5.set(digits);
        pat5[digits[0]][digits[1]][digits[2]][digits[3]].push_back(p5);
        num = vc.NextValid(num);
    }
}

void filltable(void){
    numdigits[0][0] = Prefix;
    for(vector<X____>::iterator itr1=pat1[Prefix].begin(); itr1!=pat1[Prefix].end(); ++itr1){
        for(int i=0;i<4;++i)numdigits[0][i+1]=itr1->digits[i];
        for(vector<X____>::iterator itr2=pat1[Prefix].begin(); itr2!=pat1[Prefix].end(); ++itr2){
            for(int i=0;i<4;++i)numdigits[i+1][0]=itr2->digits[i];
            for(vector<X___X>::iterator itr3=pat2[numdigits[4][0]][numdigits[0][4]].begin(); itr3 != pat2[numdigits[4][0]][numdigits[0][4]].end(); ++itr3){
                for(int i=0;i<3;++i)numdigits[3-i][1+i]=itr3->digits[i];
                for(vector<X_X__>::iterator itr4=pat3[Prefix][numdigits[2][2]].begin(); itr4!=pat3[Prefix][numdigits[2][2]].end(); ++itr4){
                    numdigits[1][1] = itr4->digits[0];
                    numdigits[3][3] = itr4->digits[1];
                    numdigits[4][4] = itr4->digits[2];
                    for(vector<XX_X_>::iterator itr5=pat4[numdigits[1][0]][numdigits[1][1]][numdigits[1][3]].begin(); itr5!=pat4[numdigits[1][0]][numdigits[1][1]][numdigits[1][3]].end(); ++itr5){
                        numdigits[1][2] = itr5->digits[0];
                        numdigits[1][4] = itr5->digits[1];
                        for(vector<XX_X_>::iterator itr6=pat4[numdigits[0][1]][numdigits[1][1]][numdigits[3][1]].begin(); itr6!=pat4[numdigits[0][1]][numdigits[1][1]][numdigits[3][1]].end(); ++itr6){
                            numdigits[2][1] = itr6->digits[0];
                            numdigits[4][1] = itr6->digits[1];
                            for(vector<XX_X_>::iterator itr7=pat4[numdigits[3][0]][numdigits[3][1]][numdigits[3][3]].begin(); itr7!=pat4[numdigits[3][0]][numdigits[3][1]][numdigits[3][3]].end(); ++itr7){
                                numdigits[3][2] = itr7->digits[0];
                                numdigits[3][4] = itr7->digits[1];
                                for(vector<XX_X_>::iterator itr8=pat4[numdigits[0][3]][numdigits[1][3]][numdigits[3][3]].begin(); itr8!=pat4[numdigits[0][3]][numdigits[1][3]][numdigits[3][3]].end(); ++itr8){
                                    numdigits[2][3] = itr8->digits[0];
                                    numdigits[4][3] = itr8->digits[1];
                                    for(vector<XXXX_>::iterator itr9=pat5[numdigits[2][0]][numdigits[2][1]][numdigits[2][2]][numdigits[2][3]].begin(); itr9!=pat5[numdigits[2][0]][numdigits[2][1]][numdigits[2][2]][numdigits[2][3]].end(); ++itr9){
                                        numdigits[2][4] = itr9->digit;
                                        for(vector<XXXX_>::iterator itr10=pat5[numdigits[0][2]][numdigits[1][2]][numdigits[2][2]][numdigits[3][2]].begin(); itr10!=pat5[numdigits[0][2]][numdigits[1][2]][numdigits[2][2]][numdigits[3][2]].end(); ++itr10){
                                            numdigits[4][2] = itr10->digit;
                                            if(!vc.IsValid(digitstonum(numdigits[4])))continue;
                                            int dig[5];
                                            for(int i=0;i<5;++i)dig[i]=numdigits[i][4];
                                            if(!vc.IsValid(digitstonum(dig)))continue;
                                            result.add();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main(){
    ifstream fin("prime3.in");
    unsigned sum;
    fin>>sum>>Prefix;
    fin.close();
    vc.Reset(sum);
    initpats();
    filltable();
    result.sort();
    ofstream fout("prime3.out");
    result.print(fout);
    fout.close();

    return 0;
}
