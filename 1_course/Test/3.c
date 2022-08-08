#include <stdio.h>
#include <string.h>
const long long mx = 100001;
int main()
{
    long long len, lena, lenb, k = 0, l = 0;
    int a[100001] = {}; int b[100001] = {};
    char s[2*mx];
    fgets(s, 200002, stdin);
    long long plus;
    scanf("%s",s);
    len = strlen(s);
    for (int i=0;i<strlen(s);i++){
        if (s[i]=='+'){
            plus = i;
        }
    }
    if (plus != 0)
    {
        for(int i = plus - 1; i > -1; i --)
        {
            a[k] = s[i] - '0';
            k += 1;
        }
        for(int i = len - 1; i > plus ; i --)
        {
            b[l] = s[i] - '0';
            l += 1;
        }
        lena = k;
        lenb = l;
        if (lena > lenb)
        {
            l = lena + 1;
            for (int i = lenb; i < l; i ++)
                b[i] = 0;
        }
        else
        {
            l = lenb + 1;
            for(int i = lena; i < l; i ++)
                a[i] = 0;
        }
        for(int i = 0; i < l; i ++)
        {
            b[i] += a[i];
            b[i + 1] += b[i] / 10;
            b[i] = b[i] % 10;
        }
        if (b[l - 1] == 0)
            l -= 1;
        for(int i = l - 1; i >- 1; i --)
            printf("%d", b[i]);
    }
    printf("\n");
}
