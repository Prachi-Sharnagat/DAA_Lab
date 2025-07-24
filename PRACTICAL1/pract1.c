#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N1 100
#define N2 10000
#define N3 1000000

float randomVal(float min, float max)
{
    return min + ((float)rand() / RAND_MAX) * (max - min);
}

void generateSensorData(float temp[], float pressure[], int n)
{
    for (int i = 0; i < n; i++)
    {
        temp[i] = randomVal(-20, 50);
        pressure[i] = randomVal(950, 1050);
    }
}

void taskA(float temp[], float pressure[], int n)
{
    float minTemp = temp[0];
    float maxPressure = pressure[0];
    for (int i = 1; i < n; i++)
    {
        if (temp[i] < minTemp)
            minTemp = temp[i];

        if (pressure[i] > maxPressure)
            maxPressure = pressure[i];
    }

    printf("task 1 : Linear Search for n = %d\n", n);
    printf("Min Temperature: %.2f\n", minTemp);
    printf("Max Pressure: %.2f\n", maxPressure);
}

void taskB(float temp[], float pressure[], int n)
{
    float minTemp, maxPressure;

    for (int i = 0; i < n; i++)
    {
        int isMin = 1;
        for (int j = 0; j < n; j++)
        {
            if (temp[i] > temp[j])
            {
                isMin = 0;
                break;
            }
        }

        if (isMin)
        {
            minTemp = temp[i];
            break;
        }
    }

    for (int i = 0; i < n; i++)
    {
        int isMax = 1;

        for (int j = 0; j < n; j++)
        {
            if (pressure[i] < pressure[j])
            {
                isMax = 0;
                break;
            }
        }

        if (isMax)
        {
            maxPressure = pressure[i];
            break;
        }
    }

    printf("task 2 : Pairwise for n = %d\n", n);
    printf("Min Temperature: %.2f\n", minTemp);
    printf("Max Pressure: %.2f\n", maxPressure);
}

int linearSearch(float arr[], int n, float target)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] >= target)
            return i;
    }
    return -1;
}

int binarySearch(float arr[], int n, float target)
{
    int low = 0, high = n - 1, answer = -1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] >= target)
        {
            answer = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return answer;
}

void generateSortedTemp(float arr[], int n)
{
    float step = (50 - 20) / (float)n;

    for (int i = 0; i < n; i++)
    {
        arr[i] = 20 + step * i;
    }
}

void taskC(int n)
{
    float *temp = (float *)malloc(n * sizeof(float));
    generateSortedTemp(temp, n);

    printf("Task 3 for n = %d:\n", n);

    int linearIndex = linearSearch(temp, n, 30);
    int binaryIndex = binarySearch(temp, n, 30);
    printf("Linear Search Index of >=30: %d, Value: %.2f\n", linearIndex, temp[linearIndex]);
    printf("Binary Search Index of >=30: %d, Value: %.2f\n", binaryIndex, temp[binaryIndex]);

    free(temp);
}

int main()
{
    srand(time(NULL));

    clock_t start, end;
    double time_spent;

    int sizes[] = {N1, N2, N3};

    for (int s = 0; s < 3; s++)
    {
        int n = sizes[s];

        float *temp = (float *)malloc(n * sizeof(float));
        float *pressure = (float *)malloc(n * sizeof(float));

        generateSensorData(temp, pressure, n);
        start = clock();
        taskA(temp, pressure, n);
        end = clock();

        time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Time taken for Task A: %.6f seconds\n\n", time_spent);

        if (n <= 10000)
        {
            start = clock();
            taskB(temp, pressure, n);
            end = clock();

            time_spent = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Time taken for Task B: %.6f seconds\n\n", time_spent);
        }

        start = clock();
        taskC(n);
        end = clock();

        time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Time taken for Task C: %.6f seconds\n\n", time_spent);
        printf("Time taken for Task C: %.6f seconds\n\n", time_spent);

        free(temp);
        free(pressure);

        return 0;
    }
