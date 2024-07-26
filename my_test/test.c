#include <stdio.h>
#include<unistd.h>

__pid_t get_ppid_of_pid(__pid_t pid) {
    char stat_file[256];
    FILE *file;
    __pid_t ppid;
    snprintf(stat_file, sizeof(stat_file), "/proc/%d/stat", pid);
    
    file = fopen(stat_file, "r");
    if (!file) {
        perror("fopen");
        return -1;
    }
    
    // The PPID is the fourth field in the stat file
    if (fscanf(file, "%*d %*s %*c %d", &ppid) != 1) {
        perror("fscanf");
        fclose(file);
        return -1;
    }
    
    fclose(file);
    return ppid;
}

void recurse_pid(int start) {
    if(start == 1) {
        return;

    } else {
        int parent_pid = get_ppid_of_pid(start);
        recurse_pid(parent_pid);
        printf("pid - %d\n", parent_pid);

    }
}

int main() {
   __pid_t current =  getpid();
  recurse_pid(current);
}