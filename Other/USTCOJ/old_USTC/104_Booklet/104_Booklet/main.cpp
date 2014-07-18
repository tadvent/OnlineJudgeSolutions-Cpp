#include<iostream>
using namespace std;
int main(){
    int pg[25][4],page,sheet;
    cin>>page;
    while(page>0){
        sheet=(page+3)/4;
        for(int i=0,fill0=4*sheet,fill1=1,fill2=2,fill3=4*sheet-1;
            i<sheet;
            ++i,fill0-=2,fill1+=2,fill2+=2,fill3-=2){
                pg[i][0]=fill0;
                pg[i][1]=fill1;
                pg[i][2]=fill2;
                pg[i][3]=fill3;
        }
        cout<<"Printing order for "<<page<<" pages:\n";
        cout<<"Sheet 1, front: ";
        if(pg[0][0]>page)cout<<"Blank";
        else cout<<pg[0][0];
        cout<<", 1\n";
        if(pg[0][2]<=page||pg[0][3]<=page){
            cout<<"Sheet 1, back : "<<"2, ";
            if(pg[0][3]>page)cout<<"Blank";
            else cout<<pg[0][3];
            cout<<'\n';
        }
        if(sheet>1){
            if(pg[1][0]<=page||pg[1][1]<=page){
                cout<<"Sheet 2, front: ";
                if(pg[1][0]>page)cout<<"Blank";
                else cout<<pg[1][0];
                cout<<", 3\n";
            }
            cout<<"Sheet 2, back : "<<pg[1][2]<<", "<<pg[1][3]<<'\n';
        }
        for(int i=2;i<sheet;++i){
            cout<<"Sheet "<<i+1<<", front: "<<pg[i][0]<<", "<<pg[i][1]<<'\n';
            cout<<"Sheet "<<i+1<<", back : "<<pg[i][2]<<", "<<pg[i][3]<<'\n';
        }
        cin>>page;
    }
    return 0;
}