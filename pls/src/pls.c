#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main()
{
        DIR* curr_dir;
        struct dirent* dr_info;

        if (NULL == (curr_dir = opendir("."))) {
                perror("curr_dir");
                return 1;
        }

        while (NULL != (dr_info = readdir(curr_dir))) {
                printf("%s\n", dr_info->d_name);
        }

        return 0;
}
