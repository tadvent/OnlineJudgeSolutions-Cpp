/*
ID: wjl1241
PROG: preface
LANG: C++
*/

#include<fstream>
using namespace std;


class roma{
public:
    //  1 5 10 50 100 500 1000
    int I,V, X, L,  C,  D,   M;
    roma():I(0),V(0),X(0),L(0),C(0),D(0),M(0){}
    roma & operator +=(int num){
        int bit=1;
        while(num!=0){
            int tmp=num%10;
            switch(tmp){
                case 9:
                    switch(bit){
                        case 1: //9
                            X+=1;
                            I+=1;
                            break;
                        case 2: //90
                            C+=1;
                            X+=1;
                            break;
                        case 3: //900
                            C+=1;
                            M+=1;
                            break;
                        case 4: //9000
                            break;
                    }
                    break;
                case 8:
                    switch(bit){
                        case 1:
                            V+=1;
                            I+=3;
                            break;
                        case 2:
                            L+=1;
                            X+=3;
                            break;
                        case 3:
                            D+=1;
                            C+=3;
                            break;
                        case 4:
                            break;
                    }
                    break;
                case 7:
                    switch(bit){
                        case 1:
                            V+=1;
                            I+=2;
                            break;
                        case 2:
                            L+=1;
                            X+=2;
                            break;
                        case 3:
                            D+=1;
                            C+=2;
                            break;
                        case 4:
                            break;
                    }
                    break;
                case 6:
                    switch(bit){
                        case 1:
                            V+=1;
                            I+=1;
                            break;
                        case 2:
                            L+=1;
                            X+=1;
                            break;
                        case 3:
                            D+=1;
                            C+=1;
                            break;
                        case 4:
                            break;
                    }
                    break;
                case 5:
                    switch(bit){
                        case 1:
                            V+=1;
                            break;
                        case 2:
                            L+=1;
                            break;
                        case 3:
                            D+=1;
                            break;
                        case 4:
                            break;
                    }
                    break;
                case 4:
                    switch(bit){
                        case 1:
                            V+=1;
                            I+=1;
                            break;
                        case 2:
                            L+=1;
                            X+=1;
                            break;
                        case 3:
                            D+=1;
                            C+=1;
                            break;
                        case 4:
                            break;
                    }
                    break;
                case 3:
                    switch(bit){
                        case 1:
                            I+=3;
                            break;
                        case 2:
                            X+=3;
                            break;
                        case 3:
                            C+=3;
                            break;
                        case 4:
                            M+=3;
                            break;
                    }
                    break;
                case 2:
                    switch(bit){
                        case 1:
                            I+=2;
                            break;
                        case 2:
                            X+=2;
                            break;
                        case 3:
                            C+=2;
                            break;
                        case 4:
                            M+=2;
                            break;
                    }
                    break;
                case 1:
                    switch(bit){
                        case 1:
                            I+=1;
                            break;
                        case 2:
                            X+=1;
                            break;
                        case 3:
                            C+=1;
                            break;
                        case 4:
                            M+=1;
                            break;
                    }
                    break;
                case 0:
                    break;
            }
            ++bit;
            num/=10;
        }
        return *this;
    }
};

int main(){
    ifstream fin("preface.in");
    ofstream fout("preface.out");

    int N;
    fin>>N;

    roma cnt;
    for(int i=1;i<=N;++i){
        cnt+=i;
    }

    if(0!=cnt.I)fout<<"I "<<cnt.I<<'\n';
    if(0!=cnt.V)fout<<"V "<<cnt.V<<'\n';
    if(0!=cnt.X)fout<<"X "<<cnt.X<<'\n';
    if(0!=cnt.L)fout<<"L "<<cnt.L<<'\n';
    if(0!=cnt.C)fout<<"C "<<cnt.C<<'\n';
    if(0!=cnt.D)fout<<"D "<<cnt.D<<'\n';
    if(0!=cnt.M)fout<<"M "<<cnt.M<<endl;

    return 0;
}