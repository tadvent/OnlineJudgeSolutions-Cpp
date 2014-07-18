#include <cstdio>

int occur, length;

bool input()
{
    char ch;
    int c;
    if(scanf(" %c ", &ch) == EOF)
        return false;
    occur = 0;
    length = 0;
    if(ch >= 'A' && ch <= 'Z')
        ch += 'a' - 'A';

    while((c = getchar()) != '\n' && c != EOF)
    {
        ++length;
        if(c == ch || c + 'a' - 'A' == ch) ++occur;
    }

    return true;
}

inline double calc()
{
    return double(occur) / length;
}

int main()
{
    while(input())
    {
        printf("%.5lf\n", calc());
    }
    return 0;
}
