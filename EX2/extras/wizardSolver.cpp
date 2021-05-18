
#include <stdio.h>
#include <string.h>
#define SIZE 28
#define F 15

void findKeyf2()
{
    const char* ref = "CIONAPGNOGKGEGPFJHEDKNIGNIBK";
    int ref_num[SIZE];
    int key[SIZE];
    const char A = 'A';

    if (strlen(ref) != SIZE)
    {
        return;
    }

    for (int i = 0; i < SIZE; i++)
    {
        ref_num[i] = ref[i] - A;
    }

    for (int k = 0; k <= F; k++)
    {
        key[1] = k;
        key[0] = key[1] ^ ref_num[0];

        for (int i = 2; i < SIZE; i++)
        {
            key[i] = key[i - 1] ^ ref_num[i - 1];
        }

        if ((key[SIZE - 1] ^ ref_num[0]) == ref_num[SIZE - 1])
        {
            //found input key !!
            break;
        }
    }

    //print result
    for (int i = 0; i < SIZE; i++)
    {
        printf("%c", key[i] + A);
    }
    printf("\n");
}

#include <iostream>
#include <vector>
#include <algorithm>
void solverf3()
{
    std::vector<int> ind = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    std::vector<int> arr = { 6, 10, 1, 2, 8, 5, 12, 7, 4 ,11, 3, 9 };
    const int target = 26;    
    
    do {

        int& x0 = arr[ind[0]];
        int& x1 = arr[ind[1]];
        int& x2 = arr[ind[2]];
        int& x3 = arr[ind[3]];
        int& x4 = arr[ind[4]];
        int& x5 = arr[ind[5]];
        int& x6 = arr[ind[6]];
        int& x7 = arr[ind[7]];
        int& x8 = arr[ind[8]];
        int& x9 = arr[ind[9]];
        int& x10 = arr[ind[10]];
        int& x11 = arr[ind[11]];

        bool B1 = (x1 + x2 + x3 + x4 == target);
        bool B2 = (x7 + x8 + x9 + x10 == target);
        bool B3 = (x0 + x2 + x5 + x7 == target);
        bool B4 = (x0 + x3 + x6 + x10 == target);
        bool B5 = (x1 + x5 + x8 + x11 == target);
        bool B6 = (x4 + x6 + x9 + x11 == target);
        bool B7 = (x0 + x1 + x4 + x7 + x10 + x11 == target);

        if (B1 && B2 && B3 && B4 && B5 && B6 && B7)
        {
            for (auto i : ind) { std::cout << i << " "; }
            std::cout << std::endl;
            return;
        }
    } while (std::next_permutation(ind.begin(), ind.end()));
}

int main()
{
    findKeyf2();
    solverf3();
    return 0;
}

