#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void nullCheck(void* ptr) {
    if (ptr == NULL) {
        printf("Out of memory!");
        exit(0);
    }
}

void fileCheck(FILE* file) {
    if (file == NULL) {
        printf("Can not open the file");
        exit(0);
    }
}

int readInt(FILE* file) {
    char str[64] = "";
    char c = 0;
    while (1) {
        c = fgetc(file);
        if (c == '\n' || c == EOF)
            break;
        strncat(str, &c, 1);
    }
    return atoi(str);
}

void printArr(int* arr, int len)
{
    printf("[");
    for (int i = 0; i < len - 1; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[len - 1]);
}

void swap(int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

int merge(int* left, int lsize, int* right, int rsize, int* res)
{
    int i = 0, j = 0, k = 0;
    int inversions = 0;
    while ((i < lsize) && (j < rsize))
        if (left[i] <= right[j])
            swap(&res[k++], &left[i++]);
        else
        {
            swap(&res[k++], &right[j++]);
            inversions += lsize - i;
        }
    while (i < lsize)
        swap(&res[k++], &left[i++]);
    while (j < rsize)
        swap(&res[k++], &right[j++]);
    return inversions;
}

int merge_sort_impl(int* arr, int len, int* buffer)
{
    if (len == 1)
        return 0;
    int middle = len / 2;
    int inversions = merge_sort_impl(arr, middle, buffer);
    inversions += merge_sort_impl(arr + middle, len - middle, buffer);
    inversions += merge(arr, middle, arr + middle, len - middle, buffer);
    for (int i = 0; i < len; i++)
        swap(&arr[i], &buffer[i]);
    return inversions;
}

int merge_sort(int* arr, int len)
{
    int* buffer = (int*)malloc(len * sizeof(int));
    nullCheck(buffer);
    int inversions = merge_sort_impl(arr, len, buffer);
    free(buffer);
    return inversions;
}

void merge_sort_inplace(int* arr, int len) {
    int unsorted = len / 2;
    merge_sort_impl(arr + unsorted, len - unsorted, arr);
    while (unsorted != 1) {
        int middle = unsorted / 2;
        merge_sort_impl(arr, middle, arr + middle);
        merge(arr, middle, arr + unsorted, len - unsorted, arr + middle);
        unsorted = middle;
    }
    for (int i = 0; (arr[i] > arr[i + 1] && i + 1 < len); swap(&arr[i++], &arr[i]));
}

int findInversionCount(int arr[], int n) // for tests
{
    int inversions = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j])
                inversions++;
    return inversions;
}


int main() {
    char nameIn[100];
    sprintf(nameIn, "C:\\Users\\volkov\\source\\repos\\MergeSort\\MergeSort\\input.txt");
    FILE* input = fopen(nameIn, "r");
    fileCheck(input);
    int len = readInt(input);
    int* arr = (int*)malloc(len * sizeof(int));
    nullCheck(arr);
    for (int i = 0; i < len; i++)
        arr[i] = readInt(input);
    fclose(input);
    printArr(arr, len);
    //merge_sort_inplace(arr, len);
    printf("%d\n", findInversionCount(arr, len));
    int inversions = merge_sort(arr, len);
    printArr(arr, len);
    printf("%d\n", inversions);
    free(arr);
}