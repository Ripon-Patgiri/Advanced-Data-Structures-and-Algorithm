#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void GenRand(int n, char name[])
{
    int i;
    FILE *f;
    f = fopen(name, "w");
    if (f == NULL)
    {
        printf("Error");
        exit(1);
    }
    srand(time(0)); // Use current time as seed for random generator
    for (i = 0; i < n; i++)
    {
        fprintf(f, "%d\n", rand() % 100);
    }
    fclose(f);
}

void ReadFromFile(int arr[], int n, char name[])
{
    int i;
    FILE *fptr;
    if ((fptr = fopen("Input.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    for (i = 0; i < n; i++)
    {
        fscanf(fptr, "%d\n", &arr[i]);
    }
    fclose(fptr);
}

void WriteToFile(int arr[], int n, char name[])
{
    int i;
    FILE *fptr;
    fptr = fopen(name, "w");
    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }
    for (i = 0; i < n; i++)
    {
        fprintf(fptr, "%d\n", arr[i]);
    }
    fclose(fptr);
}

int main()
{
    int n, i;
    printf("Enter No of Elements to be Generated :");
    scanf("%d", &n);
    int arr[n];
    clock_t s1, s2;

    GenRand(n, "Input.txt");
    ReadFromFile(arr, n, "Input.txt");
    s1 = clock();
    insertionSort(arr, n);
    s2 = clock();
    WriteToFile(arr, n, "Output.txt");

    printf("Sorting Runtime1 in Seconds : %f\n", (double)(s2 - s1) / CLOCKS_PER_SEC);

    return 0;
}