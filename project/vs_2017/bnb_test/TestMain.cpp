#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main()
{
    for (int x = 10; x > 0; x--)
    {
        for (int y = 1; y < 11; ++y)
        {
            if (y > x)
            {
                printf(" ");
            }
            else
            {
                printf("*");
            }
        }

        printf("\n");
    }

    getchar();

    return 0;
}
