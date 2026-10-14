
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;

    printf("Enter number of elements: ");

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    int *arr = malloc((size_t)n * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers: ", n);

    long long sum = 0;

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input.\n");
            free(arr);
            return 1;
        }

        sum += arr[i];
    }

    double average = (double)sum / n;

    printf("Sum = %lld\n", sum);
    printf("Average = %.2f\n", average);

    free(arr);

    return 0;
}
