// Program 18

#include <stdio.h>

void main()
{
    char sorts [8] [4] [100] = {
        {"SORT\t", "WORST CASE", "AVERAGE CASE", "BEST CASE"},
        {"Bubble\t", "O(n^2)\t", "O(n^2)\t", "O(n)"},
        {"Insertion", "O(n^2)\t", "O(n^2)\t", "O(n)"},
        {"Selection", "O(n^2)\t", "O(n^2)\t", "O(n)"},
        {"Quick\t", "O(n^2)\t", "O(nlogn)", "O(nlogn)"},
        {"Merge\t", "O(nlogn)", "O(nlogn)", "O(nlogn)"},
        {"Heap\t", "O(nlogn)", "O(nlogn)", "O(nlogn)"},
        {"Radix\t", "O(nd)\t", "O(nd)\t", "O(nd)"}
    };

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
            printf("%s\t", sorts[i][j]);
        printf("\n");
    }
}