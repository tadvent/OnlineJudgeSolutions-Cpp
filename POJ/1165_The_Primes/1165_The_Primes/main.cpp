// 1~9 开头，且各位均非零的5位质数分别为
//1: 758
//2: 702
//3: 702
//4: 692
//5: 676
//6: 640
//7: 658
//8: 635
//9: 649
//全奇数的5位质数为
//608 个
// 综上考虑先填5行5列

/*
#include<cstdio>
#include<vector>
using namespace std;
int main(){
    freopen("o.txt", "w", stdout);
    int cnt[10] = {0};
    int base, upp, num, idx, cntodd=0;
    char buf[7];
    vector<int> primes;
    primes.push_back(3);
    for(base = 3, upp = 9, num = 5; num < 100000; num += 2){
        if(num >= upp){
            ++base;
            upp = base*base;
        }
        // num < upp, sqrt(num) < base
        for(idx = 0; primes[idx] < base; ++idx)
            if(!(num % primes[idx]))break;
        if(primes[idx] >= base){
            primes.push_back(num);
            sprintf(buf, "%d", num);
            for(idx=0; idx<5; ++idx)if(!(buf[idx]) || buf[idx]=='0')break;
            if(idx>=5)++cnt[num/10000];
            for(idx=0; idx<5; ++idx)if(!((buf[idx]-'0')&0x1))break;
            if(idx>=5)++cntodd;
        }
    }
    for(idx=1; idx<10; ++idx)
        printf("%d: %d\n", idx, cnt[idx]);
    printf("all odd: %d\n", cntodd);
    //system("pause");
}
*/
///////////////////////////////////////////////////////////////
// this program is slower than USACO 4.3.2 prime3, use that fill order better.
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

// classes
class Answer{
    vector<char*> pans;
    vector<vector<char> > tans;
    struct less{
        bool operator()(const char *s1, const char *s2) const {
            return strcmp(s1, s2) < 0;
        }
    };
public:
    void add(char tb[][6]){
        tans.resize(tans.size() + 1);
        tans.back().assign(&tb[0][0], &tb[0][0]+30);
        for(int i=0; i<30; ++i)tans.back()[i] += '0';
        tans.back().push_back(0);
        for(int i=5; i<30; i+=6)tans.back()[i] = '\n';
    }
    void sort(){
        pans.resize(tans.size());
        for(int i=0; i<(int)tans.size(); ++i)
            pans[i] = &tans[i][0];
        std::sort(pans.begin(), pans.end(), less());
    }
    void output(FILE *fp)const{
        if(pans.empty()){
            fputs("NONE\n", fp);
            return;
        }
        vector<char*>::const_iterator it = pans.begin();
        fputs(*it++, fp);
        while(it != pans.end()){
            fputc('\n', fp);
            fputs(*it++, fp);
        }
    }
};

struct _____o{ // all odd digits' prime
    char dgt[5];
    _____o(char c0, char c1, char c2, char c3, char c4){
        dgt[0] = c0; dgt[1] = c1; dgt[2] = c2;
        dgt[3] = c3; dgt[4] = c4;
    }
};
struct ____Xo{ // all odd digits' prime
    char dgt[4];
    ____Xo(char c0, char c1, char c2, char c3){
        dgt[0] = c0; dgt[1] = c1; dgt[2] = c2; dgt[3] = c3;
    }
};
struct X___Xn{ // all nonzero digits' prime
    char dgt[3];
    X___Xn(char c1, char c2, char c3){
        dgt[0] = c1; dgt[1] = c2; dgt[2] = c3;
    }
};
struct X___X{
    char dgt[3];
    X___X(char c1, char c2, char c3){
        dgt[0] = c1; dgt[1] = c2; dgt[2] = c3;
    }
};
struct X_X_X{
    char dgt[2];
    X_X_X(char c1, char c3){
        dgt[0] = c1; dgt[1] = c3;
    }
};
//struct XX_XX{
//    char dgt;
//    XX_XX(char c2):dgt(c2){}
//};

// global variables
int Sum, Prefix;
bool isPrime[100000] = {0};
Answer ans;
vector<_____o> pat1;
vector<____Xo> pat2[10];
vector<X___Xn> pat3[10][10];
vector<X___X>  pat4[10][10];
vector<X_X_X>  pat5[10][10][10];
//vector<XX_XX>  pat6[10][10][10][10];

char table[5][6] = {0};

// global functions
void init(){ // fill the patterns
    int base, sqr, num, sqi, idx;
    char buf[7];
    vector<int> primes;
    primes.reserve(8000);
    primes.push_back(3);

    for(base=3, sqr=9, num=5, sqi=0; num<100000; num+=2){
        if(num >= sqr){ ++base; sqr = base*base; ++sqi; }
        for(idx=sqi; idx>=0; --idx)
            if(!(num % primes[idx]))break;
        if(idx<0){ // num is a prime
            primes.push_back(num);
            isPrime[num] = true;
            int s = 0;
            sprintf(buf, "%05d", num);
            for(int i=0; i<5; ++i){ buf[i] -= '0'; s += buf[i]; }
            if(s != Sum)continue;
            if(buf[0] && buf[1] && buf[2] && buf[3] && buf[4]){
                pat3[buf[0]][buf[4]].push_back(X___Xn(buf[1], buf[2], buf[3]));
                if((buf[0]&0x1) && buf[0] != 5
                    && (buf[1]&0x1) && buf[1] != 5
                    && (buf[2]&0x1) && buf[2] != 5
                    && (buf[3]&0x1) && buf[3] != 5
                    && (buf[4]&0x1) && buf[4] != 5){
                        pat1.push_back(_____o(buf[0], buf[1], buf[2], buf[3], buf[4]));
                        pat2[buf[4]].push_back(____Xo(buf[0], buf[1], buf[2], buf[3]));
                }
            }
            pat4[buf[0]][buf[4]].push_back(X___X(buf[1], buf[2], buf[3]));
            pat5[buf[0]][buf[2]][buf[4]].push_back(X_X_X(buf[1], buf[3]));
            //pat6[buf[0]][buf[1]][buf[3]][buf[4]].push_back(XX_XX(buf[2]));
        }
    }
}

void calc(){
    int i, s;
    table[0][0] = Prefix;
    for(vector<_____o>::const_iterator i1=pat1.begin(); i1!=pat1.end(); ++i1){
        for(i=0; i<5; ++i)table[4][i] = i1->dgt[i];
        for(vector<____Xo>::const_iterator i2=pat2[table[4][4]].begin(); i2!=pat2[table[4][4]].end(); ++i2){
            for(i=0; i<4; ++i)table[i][4] = i2->dgt[i];
            for(vector<X___Xn>::const_iterator i3=pat3[Prefix][table[0][4]].begin(); i3!=pat3[Prefix][table[0][4]].end(); ++i3){
                for(i=0; i<3; ++i)table[0][i+1] = i3->dgt[i];
                for(vector<X___Xn>::const_iterator i4=pat3[Prefix][table[4][0]].begin(); i4!=pat3[Prefix][table[4][0]].end(); ++i4){
                    for(i=0; i<3; ++i)table[i+1][0] = i4->dgt[i];
                    for(vector<X___X>::const_iterator i5=pat4[Prefix][table[4][4]].begin(); i5!=pat4[Prefix][table[4][4]].end(); ++i5){
                        for(i=0; i<3; ++i)table[i+1][i+1] = i5->dgt[i];
                        for(vector<X_X_X>::const_iterator i6=pat5[table[4][0]][table[2][2]][table[0][4]].begin(); i6!=pat5[table[4][0]][table[2][2]][table[0][4]].end(); ++i6){
                            table[3][1] = i6->dgt[0]; table[1][3] = i6->dgt[1];

                            //for(vector<XX_XX>::const_iterator i7=pat6[table[1][0]][table[1][1]][table[1][3]][table[1][4]].begin(); i7!=pat6[table[1][0]][table[1][1]][table[1][3]][table[1][4]].end(); ++i7){
                            //    table[1][2] = i7->dgt;
                            //    for(vector<XX_XX>::const_iterator i8=pat6[table[3][0]][table[3][1]][table[3][3]][table[3][4]].begin(); i8!=pat6[table[3][0]][table[3][1]][table[3][3]][table[3][4]].end(); ++i8){
                            //        table[3][2] = i8->dgt;
                            //        for(vector<XX_XX>::const_iterator i9=pat6[table[0][1]][table[1][1]][table[3][1]][table[4][1]].begin(); i9!=pat6[table[0][1]][table[1][1]][table[3][1]][table[4][1]].end(); ++i9){
                            //            table[2][1] = i9->dgt;
                            //            for(vector<XX_XX>::const_iterator i0=pat6[table[0][3]][table[1][3]][table[3][3]][table[4][3]].begin(); i0!=pat6[table[0][3]][table[1][3]][table[3][3]][table[4][3]].end(); ++i0){
                            //                table[2][3] = i0->dgt;
                            //                if(table[2][0]+table[2][1]+table[2][2]+table[2][3]+table[2][4] != Sum)continue;
                            //                if(table[0][2]+table[1][2]+table[2][2]+table[3][2]+table[4][2] != Sum)continue;
                            //                for(s=i=0; i<5; ++i) s = s*10 + table[2][i];
                            //                if(!isPrime[s])continue;
                            //                for(s=i=0; i<5; ++i) s = s*10 + table[i][2];
                            //                if(!isPrime[s])continue;
                            //                ans.add(table);
                            //            }
                            //        }
                            //    }
                            //}

                            table[1][2] = Sum-table[1][0]-table[1][1]-table[1][3]-table[1][4];
                            if(table[1][2]<0 || table[1][2]>9)continue;
                            table[3][2] = Sum-table[3][0]-table[3][1]-table[3][3]-table[3][4];
                            if(table[3][2]<0 || table[3][2]>9)continue;
                            table[2][1] = Sum-table[0][1]-table[1][1]-table[3][1]-table[4][1];
                            if(table[2][1]<0 || table[2][1]>9)continue;
                            table[2][3] = Sum-table[0][3]-table[1][3]-table[3][3]-table[4][3];
                            if(table[2][3]<0 || table[2][3]>9)continue;
                            for(s=i=0; i<5; ++i) s += table[i][2]; // sum of mid col
                            if(s != Sum)continue;
                            for(s=i=0; i<5; ++i) s += table[2][i]; // sum of mid row
                            if(s != Sum)continue;
                            for(s=i=0; i<5; ++i) s = s*10 + table[1][i]; // num of row 1
                            if(!isPrime[s])continue;
                            for(s=i=0; i<5; ++i) s = s*10 + table[2][i]; // num of row 2
                            if(!isPrime[s])continue;
                            for(s=i=0; i<5; ++i) s = s*10 + table[3][i]; // num of row 3
                            if(!isPrime[s])continue;
                            for(s=i=0; i<5; ++i) s = s*10 + table[i][1]; // num of col 1
                            if(!isPrime[s])continue;
                            for(s=i=0; i<5; ++i) s = s*10 + table[i][2]; // num of col 2
                            if(!isPrime[s])continue;
                            for(s=i=0; i<5; ++i) s = s*10 + table[i][3]; // num of col 3
                            if(!isPrime[s])continue;
                            ans.add(table);
                        }
                    }
                }
            }
        }
    }
}

// main
int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    scanf("%d%d", &Sum, &Prefix);
    init();
    calc();
    ans.sort();
    ans.output(stdout);
}
