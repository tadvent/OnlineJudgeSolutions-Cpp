/*
ID: wjl1241
PROG: friday
LANG: C++
*/

#include<fstream>
using namespace std;

int calday(int year,int month){
    int daysofmonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(month!=1)return daysofmonth[month];
    if( year%4==0 && year%100!=0 || year%400==0 )return 29;
    return 28;
}

int main(){
    ifstream fin("friday.in");
    ofstream fout("friday.out");
    int last,weekday[7],day=6;
    fin>>last;
    last=1900+last;
    for(int i=0;i<7;i++)weekday[i]=0;
    for(int year=1900;year<last;year++){
        for(int month=0;month<12;month++){
            weekday[day]++;
            day=(day+calday(year,month))%7;
        }
    }
    fout<<weekday[6];
    for(int i=0;i<6;i++)fout<<' '<<weekday[i];
    fout<<endl;
    return 0;
}