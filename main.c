#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key;
    int shmid;
    char * str;
    key = ftok("main.c", 'R');
    shmid = shmget(key, 200, 0644 | IPC_CREAT);
    str = shmat(shmid, (void *)0, 0);
    if (!strcmp(str, "")) printf("The string was just created, so it is empty.\n");
    else printf("The string is currently \"%s\".\n", str);
    printf("Do you want to change the data in the segment? [y/n]: ");
    
    char resp[1];
    scanf("%s", resp);
    if (!strcmp(resp, "y")) {
        printf("Type your new string here: ");
        char new_string[256];
        scanf("%s", new_string);
        strcpy(str, new_string);
        printf("The string is currently \"%s\"\n", str);
    }
    
    printf("Do you want to delete the data in the segment? [y/n]: ");
    scanf("%s", resp);
    if (!strcmp(resp, "y")) {
        shmctl(shmid, IPC_RMID, NULL);
    }
}
