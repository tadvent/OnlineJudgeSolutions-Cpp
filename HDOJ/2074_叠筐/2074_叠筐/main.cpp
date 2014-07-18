#include<cstdio>

char map[80][80];
int size;

void fill_circle(int pos, int len, char ch){
    for(int i=0; i<len; ++i){
        map[pos][pos+i]
        = map[pos+len-1][pos+i]
        = map[pos+i][pos]
        = map[pos+i][pos+len-1]
        = ch;
    }
}

void fill_map(char in, char out){
    for(int pos=size/2, len = 1; pos>=0; --pos, len+=2){
        if(len%4 == 1)fill_circle(pos, len, in);
        else fill_circle(pos, len, out);
    }
    if(size > 1){
        map[0][0] = map[0][size-1]
        = map[size-1][0] = map[size-1][size-1] = ' ';
    }
}

int main(){
    char in, out;
    bool first = true;
    while(scanf("%d %c %c", &size, &in, &out) != EOF){
        if(first)first=false;
        else putchar('\n');
        fill_map(in, out);
        for(int i=0; i<size; ++i){
            for(int j=0; j<size; ++j)
                putchar(map[i][j]);
            putchar('\n');
        }
    }
}
