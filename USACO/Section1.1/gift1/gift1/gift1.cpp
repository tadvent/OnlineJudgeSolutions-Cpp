/*
ID: wjl1241
PROG: gift1
LANG: C++
*/

#include<fstream>
#include<string>

using namespace std;

int findname(string thisname,string name[],int n){
    for(int i=0;i<n;i++)if(thisname==name[i])return i;
    return -1;
}

int main(){
    ifstream fin("gift1.in");
    ofstream fout("gift1.out");

    int np;
    string name[10],thisname;
    int receive[10],gift,peonum;

    for(int i=0;i<10;i++)receive[i]=0;
    fin>>np;
    for(int i=0;i<np;i++)fin>>name[i];
    while(fin>>thisname){
        int eachgift;
        string tempname;
        fin>>gift>>peonum;
        if(0!=peonum)eachgift=gift/peonum;
        else if(0!=gift) return -1;
        else continue;
        receive[findname(thisname,name,np)]-=eachgift*peonum;
        for(int i=0;i<peonum;i++){
            fin>>tempname;
            receive[findname(tempname,name,np)]+=eachgift;
        }
    }
    for(int i=0;i<np;i++){
        fout<<name[i]<<' '<<receive[i]<<endl;
    }
    return 0;
}