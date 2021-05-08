
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
        printf("%c", key[i] + 'A');
    }
    printf("\n");
}

#define ARR_SIZE 12
void solverf3()
{
    int arr2[ARR_SIZE] = { 6,10,1,2,8,5,12,7,4,11,3,9 };
    bool valid[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; i++)
    {
        valid[i] = true;
    }

    const int target = 26;

    for (int a = 0; a < ARR_SIZE; a++) if(valid[a])
    {
        int x0 = arr2[a];
        valid[a] = false;
        for (int b = 0; b < ARR_SIZE; b++)  if (valid[b])
        {
            int x1 = arr2[b];
            valid[b] = false;
            for (int c = 0; c < ARR_SIZE; c++)  if (valid[c])
            {
                int x2 = arr2[c];
                valid[c] = false;
                for (int d = 0; d < ARR_SIZE; d++) if (valid[d])
                {
                    int x3 = arr2[d];
                    valid[d] = false;
                    for (int e = 0; e < ARR_SIZE; e++) if (valid[e])
                    {
                        int x4 = arr2[e];
                        valid[e] = false;
                        for (int f = 0; f < ARR_SIZE; f++) if (valid[f])
                        {
                            int x5 = arr2[f];
                            valid[f] = false;
                            for (int g = 0; g < ARR_SIZE; g++) if (valid[g])
                            {
                                int x6 = arr2[g];
                                valid[g] = false;
                                for (int h = 0; h < ARR_SIZE; h++)  if (valid[h])
                                {
                                    int x7 = arr2[h];
                                    valid[h] = false;
                                    for (int i = 0; i < ARR_SIZE; i++)  if (valid[i])
                                    {
                                        int x8 = arr2[i];
                                        valid[i] = false;
                                        for (int j = 0; j < ARR_SIZE; j++)  if (valid[j])
                                        {
                                            int x9 = arr2[j];
                                            valid[j] = false;
                                            for (int k = 0; k < ARR_SIZE; k++)  if (valid[k])
                                            {
                                                int x10 = arr2[k];
                                                valid[k] = false;
                                                for (int l = 0; l < ARR_SIZE; l++)  if (valid[l])
												{
													int x11 = arr2[l];

													bool B1 = x1 + x2 + x3 + x4 == target;
													bool B2 = x7 + x8 + x9 + x10 == target;
													bool B3 = x0 + x2 + x5 + x7 == target;
													bool B4 = x0 + x3 + x6 + x10 == target;
													bool B5 = x1 + x5 + x8 + x11 == target;
													bool B6 = x4 + x6 + x9 + x11 == target;
													bool B7 = x0 + x1 + x4 + x7 + x10 + x11 == target;
													
													if (B1 && B2 && B3 && B4 && B5 && B6 && B7)
													{
														//printf("x: %d %d %d %d %d %d %d %d %d %d %d %d\n", x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11);
                                                        printf("i: %d %d %d %d %d %d %d %d %d %d %d %d\n", a, b, c, d, e, f, g, h, i, j, k, l);
														return;
													}
                                                }
                                                valid[k] = true;
                                            }
                                            valid[j] = true;
                                        }
                                        valid[i] = true;
                                    }
                                    valid[h] = true;
                                }
                                valid[g] = true;
                            }
                            valid[f] = true;
                        }                        
                        valid[e] = true;
                    }
                    valid[d] = true;
                }
                valid[c] = true;
            }
            valid[b] = true;
        }
        valid[a] = true;
    }
}



int main()
{
    findKeyf2();
    solverf3();
    return 0;
}

