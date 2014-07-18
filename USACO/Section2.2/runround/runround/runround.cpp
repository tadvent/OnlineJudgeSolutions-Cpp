/*
ID: wjl1241
PROG: runround
LANG: C++
*/

#include<fstream>
using namespace std;

struct node{
    bool touch;
    int num;
    node *next;
    node():touch(false),next(NULL){}
    node(int n):touch(false),num(n),next(NULL){}
};

int IsRound(int num){
    if(num%10==0)return 0;
    bool used[10];
    for(int i=1;i<10;++i)used[i]=false;
    used[0]=true;
    node *tail,*p;
    tail=new node(num%10);
    used[num%10]=true;
    tail->next=tail;
    num/=10;
    while(num){
        int bit=num%10;
        if(used[bit])break;
        used[bit]=true;
        node *newnode=new node(num%10);
        newnode->next=tail->next;
        tail->next=newnode;
        num/=10;
    }
    int result;
    if(num)result=0;
    else {
        p=tail;
        p->touch=true;
        for(;;){
            int loop=p->num;
            while(loop--)p=p->next;
            if(p->touch)break;
            p->touch=true;
        }
        if(p!=tail)result=0;
        else {
            for(p=tail->next;p!=tail;p=p->next){
                if(!(p->touch))break;
            }
            if(p!=tail)result=0;
            else result=1;
        }
    }
    for(p=tail->next;p!=tail;){
        node *tmp=p;
        p=p->next;
        delete tmp;
    }
    delete tail;
    return result;
}

int main(){
    ifstream fin("runround.in");
    ofstream fout("runround.out");
    int n;
    fin>>n;
    while(!IsRound(++n));
    fout<<n<<endl;
    return 0;
}

//==========================================================

//#include <fstream>
//#include <string>
//#include <vector>
//#include <algorithm>
//
//#define INPUT_FILE "runround.in"
//#define OUTPUT_FILE "runround.out"
//
//using namespace std;
//
//void NextNumber(std::vector<int>& number, int Digits) {
//    number[Digits - 1]++;
//    for (int i = Digits - 1; i >= 0; i--) {
//        if (number[i] == 10) {
//            number[i] = 1;
//            if (i == 0) {
//                number.insert (number.begin(),1);
//                return;
//            } else 
//                number[i - 1]++;
//        }
//    }
//    return;
//}
//
//bool CheckElement(std::vector<int>::iterator first,
//    std::vector<int>::iterator last, int val) {
//    while (first < last) {
//        if (*first == val) 
//            return true;
//        ++first;
//    }
//    return false;
//}
//
//void NextUniqueNumber(std::vector<int>& number) {
//    std::vector<int> old = number;
//    for (int i = 1; i < number.size(); ++i) {
//        if (number[i] == 0) number[i]++;
//        while (CheckElement (number.begin(),number.begin() + i,number[i])) {
//            number[i]++;
//            if (number[i] == 10) {
//                number[i] = 1;
//                NextNumber (number,i);
//                i = 1;
//                continue;
//            }
//        }
//    }
//    return;
//}
//
//bool IsRoundNumber(std::vector<int>& number) {
//    std::vector<bool> used(10,false);
//    for (int i = 0, pos = 0, val = number[0]; i < number.size(); i++) {
//        pos = (pos + val) % number.size();
//        val = number[pos];
//        if (used[pos] == true) return false;
//        used[pos] = true;
//    }
//    return true;
//}
//
//unsigned int NextRoundNumber(unsigned int number) {
//    std::vector<int> digits;
//    for (int i = 0, tens = 1; i <= 10; ++i, tens *= 10) {
//        int partial = number / tens;
//        if (partial == 0) break;
//        partial %= 10;
//        digits.push_back(partial);
//    }
//    std::reverse (digits.begin(),digits.end());
//    NextNumber (digits,digits.size());
//    NextUniqueNumber (digits);
//    while (!IsRoundNumber(digits)) {
//        NextNumber (digits,digits.size());
//        NextUniqueNumber (digits);
//    }
//    number = 0;
//    for (int i = 0; i < digits.size(); i++) 
//        number = 10 * number + digits[i];
//    return number;
//}
//
//int main(int argc, char *argv[]) {
//    ifstream FileInput (INPUT_FILE);
//    ofstream FileOutput (OUTPUT_FILE);
//    unsigned int Number;
//    FileInput >> Number;
//    FileOutput << NextRoundNumber(Number) << "\n";
//    return 0;
//}