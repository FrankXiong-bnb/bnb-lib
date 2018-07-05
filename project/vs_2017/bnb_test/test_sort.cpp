
#include "test_base.h"


void quick_sort(int* arr, int n)
{
    int sLeft[32]{ 0 }, sRight[32]{ 0 };
    int top = 0;

    int lastL = 0, lastR = n - 1;

    sLeft[top] = lastL;
    sRight[top] = lastR;
    top++;

    for (;0 < top;)
    {
        top--;
        int cL = sLeft[top];
        int cR = sRight[top];

        if (cR - cL < 1)
        {
            continue;
        }
        if (cR - cL == 1)
        {
            if (arr[cR] < arr[cL])
                arr[cL] ^= arr[cR] ^= arr[cL] ^= arr[cR];

            continue;
        }

        int mid = (cL + cR) >> 1;

        if (cR - cL == 2)
        {
            if (arr[cR] < arr[cL])
                arr[cL] ^= arr[cR] ^= arr[cL] ^= arr[cR];

            if (arr[mid] < arr[cL])
                arr[cL] ^= arr[mid] ^= arr[cL] ^= arr[mid];

            if (arr[cR] < arr[mid])
                arr[mid] ^= arr[cR] ^= arr[mid] ^= arr[cR];

            continue;
        }

        int key = arr[mid];

        int i = cL;
        int j = cR;

        for (;;)
        {
            for (; i < cR; ++i)
            {
                if (key < arr[i])
                    break;
            }

            for (; mid < j; --j)
            {
                if (!(key < arr[j]))
                    break;
            }

            if (j < i)
                break;

            if (i < j) {
                arr[i] ^= arr[j] ^= arr[i] ^= arr[j];

                ++i, --j;
            }
            else {
                --j;
            }

            if (j < i)
                break;

        }
        /*
        for (; cL < i; --i) {
            if (arr[i] < key)
                break;
        }
        */
        for (; cL < j; --j) {
            if ((arr[j] < key))
                break;
        }

        if (j - cL < cR - i)
        {
            if (i < cR)
            {
                sLeft[top] = i;
                sRight[top] = cR;
                top++;
            }
            if (cL < j)
            {
                sLeft[top] = cL;
                sRight[top] = j;
                top++;
            }
        }
        else
        {
            if (cL < j)
            {
                sLeft[top] = cL;
                sRight[top] = j;
                top++;
            }
            if (i < cR)
            {
                sLeft[top] = i;
                sRight[top] = cR;
                top++;
            }
        }
    }
   
}

void test_sort()
{
    int arr[]{ 9,4,5,6,7,2,1,8,0 };

    quick_sort(arr, 9);

    Show(arr, 9);
}

