// turn off deprecation warnings for the old functions in the CRT
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/********************************************************************** */
/* reads in 5 ints from the keyboard, calculates their exact average    */
/* (e.g., 10.92),and reports the result. Use 5 separate variables       */
/************************************************************************/
int avg1() {
    // count of the numbers which should be read from user inputs.
    int count = 5;
    // numbers to be received
    int n1, n2, n3, n4, n5;
    // a char as buffer read from the stdin.
    char c;
    double avg = 0.0;

    n1 = n2 = n3 = n4 = n5 = 0;

    puts("Input 5 int numbers and compute their average.");
    while (scanf("%d %d %d %d %d", &n1, &n2, &n3, &n4, &n5) < count) {
        while ((c = getchar()) != '\n' && c != EOF) {
            /* discard. consume the rest of input buffer. */;
        };
        puts("Your inputs:");
    };

    avg = (n1 + n2 + n3 + n4 + n5) / count;
    printf("The average: %.2f\n", avg);
    puts("\n");
    return 0;
};

/************************************************************************/
/* reads in the first number from a file. This first int number         */
/* indicates the number of subsequent floating point numbers that       */
/* appear in the file. Read the floating point numbers into an array,   */
/* and then calculate and report their average.                         */
/************************************************************************/
int avg2() {
    int count, offset;
    bool proceed = true;
    float nums[100], temp, sum;
    double avg;

    count = offset = 0;
    temp = sum = 0.0;
    avg = 0.0;

    puts("Reads numbers from numbers.txt and computer their average.\n");

    FILE* f = fopen("numbers.txt", "rb");
    if (f == NULL) {
        puts("cannot open numbers.txt. this file must be placed where this application is.");
        return 1;
    };

    while (proceed && offset - 1 < count) {
        if (fscanf(f, "%f", &temp) != 1) {
            puts("reading the count of the numbers failed.");
            proceed = false;
        } else {
            if (offset != 0) {
                nums[offset - 1] = temp;
            } else {
                count = (int)temp;
                if (count < 1) {
                    puts("reading the count of the numbers failed.");
                    proceed = false;
                };
            };
            offset++;
        };
    };
    // release the resource as soon as it is not needed.
    fclose(f);

    if (proceed) {
        // compute the average
        printf("The numbers are: ");
        for (int i = 0; i < count; i++) {
            sum += nums[i];
            printf("%.2f ", nums[i]);
        };
        printf("\n");
        avg = sum / count;
        printf("SUM = %.2f, AVG = %.2f\n", sum, avg);
    } else
        return 1;
    puts("\n");
    return 0;
}

/************************************************************************/
/* reads in the first number from a file.This first int number          */
/* indicates the number of subsequent floating point numbers that       */
/* appear in the  file.Read the floating point numbers into an array,   */
/* and then calculate and report their average.Use dynamic memory       */
/* allocation (do not use a static / statically sized array;            */
/* use a pointer)                                                       */
/************************************************************************/
int avg3() {
    int count, offset;
    float *nums, *tmp;
    float temp, sum;
    double avg = 0.0;
    bool proceed = true;

    count = offset = 0;
    temp = sum = 0.0;
    nums = tmp = NULL;

    puts("Reads numbers from numbers.txt and computer their average.\n");

    // open the file in read-only mode.
    FILE *f = fopen("numbers.txt", "rb");
    if (f == NULL) {
        puts("cannot open numbers.txt. this file must be placed where this application is.");
        return 1;
    };

    // try read the first number as the count.
    if (fscanf(f, "%f", &temp) != 1) {
        puts("reading the count of the numbers failed.");
        proceed = false;
    };

    // use the count to initialize the array
    if (proceed && temp > 0) {
        count = (int)temp;
        // allocate the memory space for the array.
        nums = (float*)malloc(sizeof(float) * count);
        // make a copy of the head address of the memory space.
        tmp = nums;
        if (nums == NULL) {
            puts("memory allocation for a float array failed.");
            proceed = false;
        };
    } else if (temp < 1) {
        proceed = false;
        puts("the count must be greater than 0.");
    };
    // read the numbers one by one
    long ending = (long)tmp + count * 4;
    while (proceed && (long)nums < ending) {
        if (fscanf(f, "%f", &temp) != 1) {
            puts("reading the numbers from the file failed.");
            proceed = false;
            break;
        }
        *nums = temp;
        nums++;
    };
    // release the resource as soon as it is not needed.
    fclose(f);

    if (proceed) {
        // compute the average
        nums = tmp;
        printf("The numbers are: ");
        for (int i = 0; i < count; i++) {
            sum += *nums;
            printf("%.2f ", *nums);
            nums++;
        };
        printf("\n");
        avg = sum / count;
        printf("SUM = %.2f, AVG = %.2f\n", sum, avg);
    }
    // free the previously allocated memory of the array.
    if (tmp != NULL)
        free(tmp);
    puts("\n");
    return 0;
};

/************************************************************************/
/* The main program execution entrance                                  */
/************************************************************************/
int main(int argc, char* argv) {
    if (avg1() != 0) {
        puts("function avg1 failed.\n");
    }
    if (avg2() != 0) {
        puts("function avg2 failed.\n");
    }
    if (avg3() != 0) {
        puts("function avg3 failed.\n");
        return 1;
    }
    return 0;
}