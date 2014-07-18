/*
ID: wjl1241
PROG: sprime
LANG: C++
*/

#include<fstream>
#include<vector>
#include<math.h>
using namespace std;

std::vector<int>::iterator find_bin(const std::vector<int>::iterator &beg,const std::vector<int>::iterator &end,const int &key){
    std::vector<int>::iterator low=beg;
    std::vector<int>::iterator high=end;
    std::vector<int>::iterator mid;
    while(low<high){
        mid=(high-low)/2+low;
        if(key==(*mid)) return mid;
        else if(key<(*mid)) high=mid;
        else low=mid+1;
    }
    return end;
}

bool isPrime(const int a){
    static std::vector<int> prime(1,3);
    if(a<2)return false;
    if(a==2)return true;
    if(a%2==0)return false;
    if(a<=prime.back()){
        if(find_bin(prime.begin(),prime.end(),a)!=prime.end())return true;
        return false;
    }
    const int
        qa=static_cast<int>(sqrt(static_cast<long double>(a)));
    for(int num=prime.back()+2;qa>prime.back();num+=2){
        if(isPrime(num))prime.push_back(num);
    }
    std::vector<int>::iterator pos=prime.begin();
    for(;pos!=prime.end();++pos){
        if((*pos)>qa)break;
        if(a%(*pos)==0)break;
    }
    if(pos==prime.end())return true;
    if((*pos)>qa)return true;
    return false;
}

vector<int> ans;

void findsprime(int lastprime,int n){
    if(0==n)ans.push_back(lastprime);
    for(int i=9;i>=0;--i)if(isPrime(lastprime*10+i))
        findsprime(lastprime*10+i,n-1);
}

int main(){
    ifstream fin("sprime.in");
    ofstream fout("sprime.out");
    int n;
    fin>>n;

    findsprime(0,n);
    for(vector<int>::reverse_iterator i=ans.rbegin();i!=ans.rend();++i)
        fout<<*i<<'\n';

    return 0;
}