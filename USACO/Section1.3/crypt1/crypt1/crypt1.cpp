/*
ID: wjl1241
PROG: crypt1
LANG: C++
*/

#include<iostream>
#include<fstream>
using namespace std;

bool allnum[10];

inline bool ass1(int num){
    return allnum[num];
}
bool ass3(int num){
    int a,b,c;
    c=num%10;
    if(!ass1(c))return false;
    a=num/100;
    if(!ass1(a))return false;
    b=num/10-a*10;
    if(!ass1(b))return false;
    return true;
}

int main(){
    for(int i=0;i<10;i++)allnum[i]=false;
    ifstream fin("crypt1.in");
    ofstream fout("crypt1.out");
    int amt,solnum=0;
    fin>>amt;
    for(int i=0;i<amt;i++){
        int tmp;
        fin>>tmp;
        allnum[tmp]=true;
    }

    int numu,numdl,numdr,an1,an2;
    for(numu=111;numu<1000;numu++){
        if(!ass3(numu))continue;
        for(numdl=1;numdl<10;numdl++){
            if(!ass1(numdl))continue;
            for(numdr=1;numdr<10;numdr++){
                if(!ass1(numdr))continue;
                an1=numu*numdr;
                if(an1>999)break;
                if(!ass3(an1))continue;
                an2=numu*numdl;
                if(an2>999)break;
                if(!ass3(an2))continue;
                amt=an1+an2*10;
                if(amt>9999)break;
                if(!ass3(amt/10))continue;
                solnum++;
            }
        }
    }
    fout<<solnum<<endl;

    return 0;
}