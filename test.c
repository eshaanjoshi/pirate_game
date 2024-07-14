#include <stdio.h>


int bounce_between(int i, int num, int offset)
{
    int d = (i) % (num * 2);
    if (d - num > 0)
    {
        return (num * 2) -d;
    }
    return d;
}

int main()
{
    int i = 0;
    while(1)
    {
        int d = bounce_between(i, 255, 0);
        printf("%d\n", d);
        i++;
    }
}