#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main()
{
    int shm_id;
    key_t key = 5678;
    char *shm_ptr;

    if ((shm_id = shmget(key, SHM_SIZE, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm_ptr = shmat(shm_id, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    printf("Message read from shared memory: %s\n", shm_ptr);

    shmdt(shm_ptr);

    return 0;
}

