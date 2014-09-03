#include<cstdio>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

class Solution
{
public:
    int longestValidParentheses(string s) {
        if(s.empty()) return 0;
        vector<int> dp;
        vector<int> pstack;
        for(int i = 0; i != s.length(); ++i){
            switch(s[i]){
            case '(':
                if(dp.empty() || s[i-1] == '('){
                    dp.push_back(0);
                } else {
                    dp.push_back(dp.back());
                }
                pstack.push_back(i);
                break;
            case ')':
                if(pstack.empty()){
                    dp.push_back(0);
                } else {
                    dp.push_back(i-pstack.back()+1+dp[pstack.back()]);
                    pstack.pop_back();
                }
                break;
            default:
                exit(-1);
                break;
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};

int main(){
    Solution s;
    char a[][20] = {
        "()()()",
        "())((()))",
        "))()(()()))())",
        ")()())",
        "(((",
        "))(",
        ""
    };
    int n = sizeof(a)/sizeof(a[0]);
    for(int i=0; i<n; ++i){
        printf("%d\n", s.longestValidParentheses(a[i]));
    }
    system("pause");
}
