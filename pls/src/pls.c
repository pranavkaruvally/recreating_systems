#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#define FILE_DATA_LEN 512

static struct options {
        unsigned int long_list      : 1;
        unsigned int all_files      : 1;
        unsigned int human_readable : 1;
}options;

char* format_time(struct tm*);
char* file_perm(mode_t);

int main(int argc, char** argv)
{
        DIR* curr_dir;
        struct dirent*  dr_info;
        struct stat     statbuf;
        struct passwd*  pwd;
        struct group*   grp;

        char  file_data[FILE_DATA_LEN];
        int   file_data_len = 0;
        int   opt;

        memset(&options, 0, sizeof(struct options));
        while(-1 != (opt = getopt(argc, argv, "hal"))) {
                switch(opt) {
                        case 'a':
                                options.all_files = 1;
                                break;
                        case 'l':
                                options.long_list = 1; 
                                break;
                        case 'h': // Case not implemented
                                options.human_readable = 1;
                                break;
                        case '?':
                                fprintf(stderr, "pls: invalid option -- %c\n", opt);
                                break;
                        default:
                                fprintf(stderr, "pls: invalid option -- %c\n", opt);
                                break;
                }
        }

        if (NULL == (curr_dir = opendir("."))) {
                perror("curr_dir");
                return 1;
        }

        while (NULL != (dr_info = readdir(curr_dir))) {
                memset(file_data, 0, FILE_DATA_LEN);
                file_data_len = 0;

                if (-1 == stat(dr_info->d_name, &statbuf)) {
                        continue;
                }
                if (0 == options.all_files && '.' == dr_info->d_name[0]) {
                        continue;
                }

                if (1 == options.long_list) {
                        file_data_len += \
                                sprintf(file_data + file_data_len, "%.11s ", file_perm(statbuf.st_mode));
                        file_data_len += \
                                sprintf(file_data + file_data_len, "%3ld ", statbuf.st_nlink);

                        if (NULL != (pwd = getpwuid(statbuf.st_uid))) {
                                file_data_len += \
                                        sprintf(file_data + file_data_len, "%-.8s ", pwd->pw_name);
                        } else {
                                file_data_len += \
                                        sprintf(file_data + file_data_len, "%-8d ", statbuf.st_uid);
                        }
                        if (NULL != (grp = getgrgid(statbuf.st_gid))) {
                                file_data_len += \
                                        sprintf(file_data + file_data_len, "%-.8s ", grp->gr_name);
                        } else {
                                file_data_len += \
                                        sprintf(file_data + file_data_len, "%-8d ", statbuf.st_gid);
                        }

                        file_data_len += sprintf(                      \
                                file_data + file_data_len,              \
                                "%9jd %.12s ",                           \
                                (intmax_t)statbuf.st_size,                \
                                format_time(localtime(&statbuf.st_mtime))  \
                        );
                }
                file_data_len += \
                        sprintf(file_data + file_data_len, "%s", dr_info->d_name);
                printf("%s\n", file_data);
        }

        return 0;
}

char* file_perm(mode_t mode)
{
        static const mode_t modes[9] = {
                S_IRUSR, S_IWUSR, S_IXUSR, 
                S_IRGRP, S_IWGRP, S_IXGRP, 
                S_IROTH, S_IWOTH, S_IXOTH
        };

        static const char perm_chars[3] = { 'r', 'w', 'x' };

        static char perm[11];
        memset(perm, '-', 11);

        switch(S_IFMT & mode) {
                case S_IFBLK:
                        perm[0] = 'b';
                        break;
                case S_IFCHR:
                        perm[0] = 'c';
                        break;
                case S_IFLNK:
                        perm[0] = 'l';
                        break;
                case S_IFDIR:
                        perm[0] = 'd';
                        break;
                case S_IFIFO:
                        perm[0] = 'p';
                        break;
                case S_IFSOCK:
                        perm[0] = 's';
                        break;
                default:                // S_IFREG
                        break;
        }
        
        for (int i=0; i < 9; i++) {
                if (modes[i] & mode) {
                        perm[i+1] = perm_chars[i%3];
                }
        }

        return perm;
}

char* format_time(struct tm *timep)
{
        static char date_string[15];
        static const char months[12][3] = {
                "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
        };

        sprintf(                                                                   \
                date_string,                                                        \
                "%.3s %d %.2d:%.2d",                                                 \
                months[timep->tm_mon], timep->tm_mday, timep->tm_hour, timep->tm_min  \
        );
        
        return date_string;
}
