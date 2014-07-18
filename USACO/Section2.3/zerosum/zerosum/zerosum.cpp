/*
ID: wjl1241
PROG: zerosum
LANG: C++
*/

#include<fstream>
#include<vector>
#include<string>
#include<stack>
using namespace std;

int pre(char op1,char op2){
    int matrix[3][3]={
        {-1,-1,-1},
        { 1,-1,-1},
        { 1,-1,-1}
    };

    switch(op1){
        case ' ':
            op1=0;
            break;
        case '+':
            op1=1;
            break;
        case '-':
            op1=2;
            break;
    }
    switch(op2){
        case ' ':
            op2=0;
            break;
        case '+':
            op2=1;
            break;
        case '-':
            op2=2;
            break;
    }
    return matrix[op1][op2];
}

bool nextop(string &ops){
    int i=ops.length()-1;
    while(i>=0){
        if(ops[i]!='-')break;
        --i;
    }
    if(i<0)return false;
    if(ops[i]==' ')ops[i]='+';
    else ops[i]='-';
    for(int j=i+1;j<ops.length();++j)ops[j]=' ';
    return true;
}

int calc(string ops){
    int n=ops.length()+1;
    vector<int> num(n);
    for(int i=0;i<n;++i)num[i]=i+1;

    stack<int> ssum;
    stack<char> sch;
    ssum.push(num[0]);
    sch.push(ops[0]);
    for(int i=0;i<ops.length();){
        if(i==ops.length()-1){
            while(!sch.empty()){
                switch(sch.top()){
                    case ' ':
                        num[i+1]=ssum.top()*10+num[i+1];
                        break;
                    case '+':
                        num[i+1]=ssum.top()+num[i+1];
                        break;
                    case '-':
                        num[i+1]=ssum.top()-num[i+1];
                        break;
                }
                sch.pop();
                ssum.pop();
            }
            return num[i+1];
        }
        if(!sch.empty() && pre(sch.top(),ops[i+1])<0){
                switch(sch.top()){
                    case ' ':
                        num[i+1]=ssum.top()*10+num[i+1];
                        break;
                    case '+':
                        num[i+1]=ssum.top()+num[i+1];
                        break;
                    case '-':
                        num[i+1]=ssum.top()-num[i+1];
                        break;
                }
                sch.pop();
                ssum.pop();
            //ssum.push(num[i+1]);
        }
        else {
            ssum.push(num[i+1]);
            sch.push(ops[i+1]);
            ++i;
        }
    }
    return -1;
}

int main(){
    ifstream fin("zerosum.in");
    ofstream fout("zerosum.out");

    int n;
    string ops;
    fin>>n;
    ops.resize(n-1);
    ops.assign(n-1,' ');
    do{
        if(0==calc(ops)){
            fout<<1;
            for(int i=0;i<ops.length();++i)fout<<ops[i]<<i+2;
            fout<<'\n';
        }
    }while(nextop(ops));

    return 0;
}