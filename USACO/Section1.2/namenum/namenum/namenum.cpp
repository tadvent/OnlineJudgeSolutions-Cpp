#include"rotator.h"
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

int compare(const string& str1, const string& str2){
    int minlen=((str1.length()<str2.length())?str1.length():str2.length());
    for(int i=0;i<minlen;i++){
        if(str1[i]>str2[i])return 1;
        else if(str1[i]<str2[i])return -1;
    }
    if(str1.length()>str2.length())return 1;
    else if(str1.length()<str2.length())return -1;
    else return 0;
}

int main(){
    rotator<char> rname;
    vector<char> botton[10];
    char letters[]={'A','B','C',    //2
                    'D','E','F',    //3
                    'G','H','I',    //4
                    'J','K','L',    //5
                    'M','N','O',    //6
                    'P','R','S',    //7
                    'T','U','V',    //8
                    'W','X','Y'};   //9
    string numin;
    vector<string> dict;
    ifstream fin("namenum.in");
    ifstream indict("dict.txt");
    ofstream fout("namenum.out");
    fin>>numin;
    string tempin;
    while(indict>>tempin)dict.push_back(tempin);
    indict.close();
    for(int i=2;i<10;i++)botton[i].assign(letters+i*3-6,letters+i*3-3);
    for(int i=0;i<numin.length();i++){
        rname.push_back(botton[static_cast<int>(numin[i])-48]);
    }

    int stat=0;
    int dictptr=0;
    bool finish=false;
    bool hasprinted=false;
    while(!finish){
        stat=compare(rname.strout(),dict[dictptr]);
        switch(stat){
            case 1:if(++dictptr>=dict.size())finish=true;
                break;
            case -1:if(!rname.turn())finish=true;
                break;
            default:fout<<dict[dictptr]<<endl;
                if(++dictptr>=dict.size())finish=true;
                if(!rname.turn())finish=true;
                hasprinted=true;
        }
    }
    if(!hasprinted)fout<<"NONE"<<endl;

    fin.close();
    fout.close();
    return 0;
}