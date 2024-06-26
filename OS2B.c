#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SIZE 100

void sort_array(int arr[], int n) {
    // bubble sort
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int arr[MAX_SIZE];
    int n;

    printf("Enter the size of the array (maximum size is %d): ", MAX_SIZE);
    scanf("%d", &n);

    printf("Enter the array elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // create a child process
    pid_t pid = fork();

    if (pid == -1) {
        printf("Failed to create child process!\n");
        return 1;
    } else if (pid == 0) {
        // child process
        char *args[n+2]; // +2 for command name and NULL
        args[0] = "display_reverse"; // command name
        for (int i = 0; i < n; i++) {
            args[i+1] = malloc(sizeof(char)*5); // allocate memory for each argument
            sprintf(args[i+1], "%d", arr[i]); // convert integer to string
        }
        args[n+1] = NULL; // last argument should be NULL

        execve("./display_reverse", args, NULL); // load new program
    } else {
        // parent process
        wait(NULL); // wait for child process to finish

        sort_array(arr, n); // sort the array

        printf("Sorted array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    return 0;
}

