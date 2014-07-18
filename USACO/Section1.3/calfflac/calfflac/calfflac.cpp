/*
ID: wjl1241
PROG: calfflac
LANG: C++
*/

//#include<istream>
#include<fstream>
//#include<vector>
//#include<algorithm>
using namespace std;

//vector<char> inall;
char inall[20001];
int istrlength=0,maxlen=0,beg,end;

inline bool isletter(const char c){
    return (c>='a'&&c<='z')||(c>='A'&&c<='Z');
}

bool nextpre(int &pre, const int axis){
    do {--pre;
        if(pre<0||(axis-pre)>1000)return false;
    }while(!isletter(inall[pre]));
    return true;
}

bool nextbak(int &bak, const int axis){
    do {++bak;
        if(bak>=istrlength||(bak-axis)>1000)return false;
    }while(!isletter(inall[bak]));
    return true;
}

inline bool equal(char c1, char c2){
    return (c1==c2||(c1-c2=='a'-'A')||(c2-c1=='a'-'A'));
}

void findmaxlen(const int axis){
    int pre=axis,bak=axis,len=1;
    int trypre=pre,trybak=bak;
    while(nextpre(trypre,axis)&&nextbak(trybak,axis)){
        if(!equal(inall[trypre],inall[trybak]))break;
        len+=2;
        pre=trypre;
        bak=trybak;
    }
    if(len>maxlen){
        maxlen=len;
        beg=pre;
        end=bak+1;
    }

    pre=axis+1,bak=axis,len=0;
    trypre=pre,trybak=bak;
    while(nextpre(trypre,axis)&&nextbak(trybak,axis)){
        if(!equal(inall[trypre],inall[trybak]))break;
        len+=2;
        pre=trypre;
        bak=trybak;
    }
    if(len>maxlen){
        maxlen=len;
        beg=pre;
        end=bak+1;
    }
}

int main(){
    ifstream fin("calfflac.in");
    ofstream fout("calfflac.out");

    //fin.unsetf(ios::skipws);
    //copy(istream_iterator<char>(fin),istream_iterator<char>(),back_inserter(inall));
    //copy(inall.begin(),inall.end(),ostream_iterator<char>(fout));

    for(char c;(c=fin.get())!=EOF;++istrlength)inall[istrlength]=c;
    //fout.write(inall,istrlength);
    for(int i=0;i<istrlength-1;++i)if(isletter(inall[i]))findmaxlen(i);
    fout<<maxlen<<endl;
    fout.write(&inall[beg],end-beg);
    fout.put('\n');

    system("pause");
    return 0;
}