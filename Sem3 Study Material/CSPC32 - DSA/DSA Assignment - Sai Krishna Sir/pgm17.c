// Program 17

#include <stdio.h>
#include <stdlib.h>

// Swap Elements at 2 positions
void swap(int * A, int x, int y)
{
    int tmp = *(A + x);
    *(A + x) = *(A + y);
    *(A + y) = tmp;
}

// Bubble Sort
void Bsort(int * A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            // check condition to do swapping
            if (*(A + j) > *(A + j + 1))
                swap(A, j, j+1); // swap adjcent elements
        }
    }
}

// Selection Sort
void Ssort(int * A, int n)
{
    for (int i = 0; i < n; i++)
    {
        int sml = *(A + i), p = i; // smallest element and position
        for (int j = i+1; j < n; j++)
        {
            if (*(A + j) < sml)
            {
                sml = *(A + j);
                p = j; // update smallest element and position
            }
        }
        swap(A, i, p); // swap elements at ith and pth positions
    }
}

// Insertion Sort
void Isort(int * A, int n)
{
    for (int i = 0; i < n; i++)
    {
        int val = *(A + i);
        int j;
        for (j = i; (j > 0) && (*(A + j - 1) > val); j--)
            *(A + j) = *(A + j - 1);
        *(A + j) = val;
    }
}

// Radix Sort
int getMax(int arr [], int n)
{
    int mx = arr[0]; // maximum element
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i]; // update maximum
    return mx; // return maximum element in array
}

void countSort(int arr [], int n, int exp) // count sort digit by digit
{
    int output[n]; // output array
    int count [10] = { 0 };
    
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++; // fill counts
    for (int i = 1; i < 10; i++)
        count[i] += count[i-1]; // fill cumulative counts
    for (int i = n-1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i]; // fill output
        count[(arr[i] / exp) % 10]--; // reduce count
    }
    for (int i = 0; i < n; i++)
        arr[i] = output[i]; // copy back into original array
}

void Rsort(int arr [], int n) // main radix sort code
{
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

// Merge Sort
void merge(int * A, int L, int U)
{
    int M = (L + U) / 2;
    int * B = (int *) malloc((U-L+1) * sizeof(int));
    int P1 = L, P2 = M+1, P = 0; // pointers to arrays
    
    // Compare and insert into new array
    while (P1 <= M && P2 <= U)
    {
        if (*(A + P1) < *(A + P2))
            *(B + (P++)) = *(A + (P1++));
        else
            *(B + (P++)) = *(A + (P2++));
    }

    // Insert remaining elements into new array
    while (P1 <= M)
        *(B + (P++)) = *(A + (P1++));
    while (P2 <= U)
        *(B + (P++)) = *(A + (P2++));
    
    // Copy values from new array into original array
    int P3 = L; P = 0;
    while (P3 <= U)
        *(A + (P3++)) = *(B + (P++));
}

void M_sort(int * A, int L, int U)
{
    if (L == U) return; // base case
    int M = (L + U) / 2;
    M_sort(A, L, M); // sort left half
    M_sort(A, M+1, U); // sort right half
    merge(A, L, U); // merge sorted halves
}

void Msort(int * A, int n)
{
    M_sort(A, 0, n-1); // set default limits as 0 to n-1 (whole array)
}

// Quick Sort
int partition(int * A, int L, int U)
{
    int i = L-1;
    int pivot = *(A + U);

    for (int j = L; j < U; j++)
    {
        if (*(A + j) < pivot)
        {
            i++;
            swap(A, i, j); // swap
        }
    }

    swap(A, i+1, U); // final swap
    return (i+1);
}

void Q_sort(int * A, int L, int U)
{
    if (L < U) // L >= U is termination case
    {
        int P = partition(A, L, U); // get correct position of pivot
        Q_sort(A, L, P-1); // sort left of pivot
        Q_sort(A, P+1, U); // sort right of pivot
    }
}

void Qsort(int * A, int n)
{
    Q_sort(A, 0, n-1); // set default limits as 0 to n-1
}

// Heap sort
void heapify(int * arr, int N, int i)
{
    int largest = i;
    int left = (2 * i) + 1; // left child
    int right = (2 * i) + 2; // right child

    if (left < N && arr[left] > arr[largest]) // left is greater than root
        largest = left;
    if (right < N && arr[right] > arr[largest]) // right is greater than root
        largest = right;
    
    if (largest != i) // largest is not root
    {
        swap(arr, largest, i);
        heapify(arr, N, largest); // heapify at child position
    }
}

void Hsort(int * arr, int N)
{
    for (int i = (N/2)-1; i >= 0; i--)
        heapify(arr, N, i); // heapify starting from parent of last leaf
    
    for (int i = N-1; i >= 0; i--)
    {
        swap(arr, 0, i); // swap root and last element
        heapify(arr, i, 0); // heapify root
    }
}

void main()
{
    printf("Welcome to C Array Sorter !\n");
    printf("7 sorts are available : Bubble (B), Selection (S), Insertion (I), Radix (R), Merge (M), Quick (Q), Heap (H).\n\n");

    int n; // number of elements
    printf("Enter the number of elements : ");
    scanf("%d", &n);

    int * arr = (int *) malloc(n * sizeof(int));
    printf("Enter the unsorted array : ");
    for (int i = 0; i < n; i++)
        scanf("%d", arr+i);
    
    char ch; // choice of sort
    printf("Enter your choice of sort : ");
    scanf(" %c", &ch);

    switch(ch)
    {
        case 'B': Bsort(arr, n); break;
        case 'S': Ssort(arr, n); break;
        case 'I': Isort(arr, n); break;
        case 'R': Rsort(arr, n); break;
        case 'M': Msort(arr, n); break;
        case 'Q': Qsort(arr, n); break;
        case 'H': Hsort(arr, n); break;
        default: printf("Invalid Sort."); break;
    }

    printf("Sorted Array : ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    
    printf("\n\nThank you for using C Array Sorter. Bye Bye !");
}