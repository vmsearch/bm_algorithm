#include <stdio.h>
#include <string.h>
#define MAX(x, y) (x) > (y) ? (x) : (y)

void stuffixes(int *stuff, int m, char*pattern)
{
    int i;
    int j;
    stuff[m-1] = m;
    for (i = m - 2; i > 0; i --){
        j = i;
        while (j >= 0 && pattern[j] == pattern[m - 1 - i + j])
            --j;
        stuff[i] = i - j;
        

    }

}

void bmBc(int *bmbc,char *pattern, int m){
    int i;
    int j;

    for (i = 0; i < 256; i ++)
            bmbc[i] =  m;

    for (i = 0 ; i < m - 1; i++){
        bmbc[pattern[i]] = m -i -1;
    }
}

void bmGc(int *bmgc, char *pattern, int m){
    int i;
    int j;
    int stuff[256];
    stuffixes(stuff, m, pattern);
    for (i = 0; i < m; i++)
        bmgc[i] = m;

    j = 0;
    for (i = m - 1; i >= 0; i --) {
        if (stuff[i] == i + 1){
            for (; j < m -1 -i; j++){
                if (bmgc[j] == m)
                    bmgc[j] = m - 1 - i;
            }
        }
    }

    for (i = 0; i < m - 1; i ++) {
        printf("stuff[%d] is %d\n",i, stuff[i] );
        bmgc[m - 1 - stuff[i]] = m - 1 - i;
    }
}

int BoyerMoore(char *pattern, int m, char *text, int n) {

    int i;
    int j;
    int bmgc[256];
    int bmbc[256];
    bmBc(bmbc, pattern, strlen(pattern));
    bmGc(bmgc,pattern, strlen(pattern));

    j = 0;
    while (j <= n - m) {
          for (i = m - 1; i >= 0 && pattern[i] == text[i + j]; --i);
          if (i < 0) {
                 printf("find it at the position %d\n",j);
                 j += bmgc[0];
                 return 0;
              }
          else
              j += MAX(bmgc[i], bmbc[text[i + j]] - m + 1 + i);
    }
    printf("not find the %s\n", pattern);
    return  -1;
}

int main(void)
{
    char pattern[32] = "example";
    char text[128] = "there is my father";
    BoyerMoore(pattern, strlen(pattern), text, strlen(text));
    return 1;
}


