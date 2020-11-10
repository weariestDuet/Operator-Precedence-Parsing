#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

char input[1001];
char store[1001];
int top = 0;
int matrix[6][7] = {
    { 1,-1,-1, 1,-1, 1},
    { 1, 1,-1, 1,-1, 1},
    {-1,-1,-1, 0,-1,-2},
    { 1, 1, 0, 1, 0, 1},
    { 1, 1, 0, 1,-2, 1},
    {-1,-1,-1,-1,-1, 0}
};

int isTerminal(char c)
{
    if(c!='N') return 1;
	return 0;
}

int reduce()
{
    if(top <= 1) return false; // 此时栈中只有'#'
    else if(store[top-1] == 'i')
    {
        printf("R\n");
        store[top-1] = 'N';
    }
    else if(store[top-1] == ')')
    {
        if(top<=3||store[top-3]!='('||store[top-2]!='N') return false;
        printf("R\n");
        top-=3;
        store[top++] = 'N';
    }

    else if(store[top-1] == 'N')
        return true;
    else return false;
    return true;
}
int getPr(char c)
{
    switch (c)
    {
    case '+':
        return 0;
    case '*':
        return 1;
    case '(':
        return 2;
    case ')':
        return 3;
    case 'i':
        return 4;
    case '#':
        return 5;
    default:
        return -1;
    }
}

int main()
{
    scanf("%s", input);
    int len = strlen(input);
    input[len] = '#';
    input[len+1] = '\0';
    top = 0;
    // 先将开始符号移动入栈
    store[top++] = '#';
    int i=0;
    while (i<=len)
    {
        int t = top-1;
        while (t >= 0 && !isTerminal(store[t]))
            t--;
        if (t < 0)
            return printf("RE\n"), 0;
        int u = getPr(store[t]);
        int v = getPr(store[i]); 
        if (v == -1 || u == -1 || matrix[u][v] == -2)
            return printf("E\n"), 0;
        if(v == 5 && u == 5) break;
        if (matrix[u][v] <= 0) 
        {
            printf("I%c\n",store[i]);
            store[top++] = store[i];
            i++;
        }
        else
        { 
            if(top < 2) return printf("RE\n"),0;

            if(!reduce()) return printf("RE\n"),0;
        }
    }

    if(top > 2) printf("RE\n");
    return 0;
}