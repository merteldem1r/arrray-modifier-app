#include <stdio.h>
#include <stdlib.h>

#include "../include/array.h"
#include "../include/core_methods.h"
#include "../include/utils.h"

// Optional: Resizing for dynamic array implementation
void Resize(struct Array *arr) {
    arr->size *= 2;
    int *temp = (int *) realloc(arr->A, arr->size * sizeof(int));

    if (temp == NULL) {
        printf("**Error: Memory reallocation failed!");
        free(arr->A);
        exit(1);
    }

    arr->A = temp;
}

void Display(const struct Array *arr) {
    const char *COLOR = C_DATA;
    printf("%sArray:%s { ", COLOR, P_RESET);

    if (arr->length > 10) {
        for (int i = 0; i < 5; ++i)
            printf("%d ", arr->A[i]);

        printf("... ");

        for (int i = arr->length - 5; i < arr->length; ++i)
            printf("%d ", arr->A[i]);
    } else {
        for (int i = 0; i < arr->length; ++i)
            printf("%d ", arr->A[i]);
    }
    printf("} %sLength:%s %d", COLOR, P_RESET, arr->length);
}

void Append(struct Array *arr, int num) {
    if (arr->size == arr->length) {
        printf("\t\t** Error: No empty space to Append");
        return;
    }

    arr->A[arr->length] = num;
    ++arr->length;
}

void Insert(struct Array *arr, int index, int num) {
    if (arr->size == arr->length) {
        printf("\t\t** Error: No empty space to Insert\n");
        return;
    }

    if (index < 0 || index > arr->length) {
        printf("\t\t** Error: Invalid index. Index should be between 0 and %d\n", arr->length);
        return;
    }

    if (index == arr->length) {
        Append(arr, num);
        return;
    }

    for (int i = arr->length; i > index; --i)
        arr->A[i] = arr->A[i - 1];

    arr->A[index] = num;
    ++arr->length;
}

int Delete(struct Array *arr, int index, int *resPtr) {
    if (index < 0 || index >= arr->length) {
        printConsoleMessage(0, "Invalid index for Delete");
        return -1;
    }

    const int x = arr->A[index];

    for (int i = index; i < arr->length - 1; ++i) {
        arr->A[i] = arr->A[i + 1];
    }

    --arr->length;
    arr->A[arr->length] = 0;

    if (resPtr != NULL)
        *resPtr = x;

    return x;
}

int Get(const struct Array *arr, int index, int *resPtr) {
    if (index < 0 || index >= arr->length) {
        printf("Error: Invalid index to Get\n");
        return -1;
    }

    const int val = arr->A[index];

    if (resPtr != NULL)
        *resPtr = val;

    return val;
}

int Set(const struct Array *arr, int index, int num, int *resPtr) {
    if (index < 0 || index >= arr->length) {
        printf("Error: Invalid index to Set\n");
        return -1;
    }

    arr->A[index] = num;
    const int val = arr->A[index];

    if (resPtr != NULL)
        *resPtr = val;

    return val;
}
