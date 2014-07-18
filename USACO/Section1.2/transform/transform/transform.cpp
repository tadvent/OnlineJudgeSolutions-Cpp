/*
ID: wjl1241
PROG: transform
LANG: C++
*/

#include<iostream>
#include<fstream>
using namespace std;

int n;
const int MAXN=10;
char table1[MAXN][MAXN],table2[MAXN][MAXN];

bool rotate1(){
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)
        if(table1[i][j]!=table2[j][n-1-i])return false;
    return true;
}

bool rotate2(){
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)
        if(table1[i][j]!=table2[n-1-i][n-1-j])return false;
    return true;
}

bool rotate3(){
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)
        if(table1[i][j]!=table2[n-1-j][i])return false;
    return true;
}

bool reflect(){
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)
        if(table1[i][j]!=table2[i][n-1-j])return false;
    return true;
}

bool combine(){
        int i,j;
        for(i=0;i<n;i++)for(j=0;j<n;j++)if(table1[i][j]!=table2[j][i])goto pos1;
pos1:   if(i==n&&j==n)return true;
        for(i=0;i<n;i++)for(j=0;j<n;j++)if(table1[i][j]!=table2[n-1-i][j])goto pos2;
pos2:   if(i==n&&j==n)return true;
        for(i=0;i<n;i++)for(j=0;j<n;j++)if(table1[i][j]!=table2[n-1-j][n-1-i])goto pos3;
pos3:   if(i==n&&j==n)return true;
        return false;
}

bool nochange(){
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)
        if(table1[i][j]!=table2[i][j])return false;
    return true;
}

int recognize(){
    int i=0;
    typedef bool (*funp)();
    funp fun[6]={rotate1,rotate2,rotate3,reflect,combine,nochange};
    for(;i<6;i++)if((fun[i])())return i+1;
    return i+1;
}

int main(){
    ifstream fin("transform.in");
    ofstream fout("transform.out");
    fin>>n;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)fin>>table1[i][j];
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)fin>>table2[i][j];
    fout<<recognize()<<endl;
    fin.close();
    fout.close();

    return 0;
}